// 7z/Handler.h

#pragma once

#ifndef __7Z_HANDLER_H
#define __7Z_HANDLER_H

#include "../IArchive.h"
// #include "../../../Compress/Interface/CompressInterface.h"
#include "7zIn.h"

#include "7zCompressionMode.h"

#ifndef _SFX
#include "7zMethods.h"
#endif

namespace NArchive {
namespace N7z {

#ifndef EXTRACT_ONLY

struct COneMethodInfo
{
  CObjectVector<CProperty> CoderProperties;
  UString MethodName;
};
#endif

// {23170F69-40C1-278A-1000-000110050000}
DEFINE_GUID(CLSID_CFormat7z, 
  0x23170F69, 0x40C1, 0x278A, 0x10, 0x00, 0x00, 0x01, 0x10, 0x05, 0x00, 0x00);

class CHandler: 
  public IInArchive,
  #ifndef EXTRACT_ONLY
  public IOutArchive, 
  public ISetProperties, 
  #endif
  public CMyUnknownImp
{
public:
  #ifdef EXTRACT_ONLY
  MY_UNKNOWN_IMP
  #else
  MY_UNKNOWN_IMP3(
      IInArchive,
      IOutArchive,
      ISetProperties
      )
  #endif

  STDMETHOD(Open)(IInStream *stream, 
      const UINT64 *maxCheckStartPosition,
      IArchiveOpenCallback *openArchiveCallback);  
  STDMETHOD(Close)();  
  
  STDMETHOD(GetNumberOfItems)(UINT32 *numItems);  
  STDMETHOD(GetProperty)(UINT32 index, PROPID propID,  PROPVARIANT *value);
  STDMETHOD(Extract)(const UINT32* indices, UINT32 numItems, 
      INT32 testMode, IArchiveExtractCallback *extractCallback);

  STDMETHOD(GetArchiveProperty)(PROPID propID, PROPVARIANT *value);

  STDMETHOD(GetNumberOfProperties)(UINT32 *numProperties);  
  STDMETHOD(GetPropertyInfo)(UINT32 index,     
      BSTR *name, PROPID *propID, VARTYPE *varType);

  STDMETHOD(GetNumberOfArchiveProperties)(UINT32 *numProperties);  
  STDMETHOD(GetArchivePropertyInfo)(UINT32 index,     
      BSTR *name, PROPID *propID, VARTYPE *varType);


  #ifndef EXTRACT_ONLY
  // IOutArchiveHandler
  STDMETHOD(UpdateItems)(IOutStream *outStream, UINT32 numItems,
      IArchiveUpdateCallback *updateCallback);

  STDMETHOD(GetFileTimeType)(UINT32 *type);  

  // ISetProperties
  STDMETHOD(SetProperties)(const BSTR *names, const PROPVARIANT *values, INT32 numProperties);
  #endif

  CHandler();

private:
  CMyComPtr<IInStream> _inStream;

  NArchive::N7z::CArchiveDatabaseEx _database;

  #ifndef EXTRACT_ONLY
  CObjectVector<COneMethodInfo> _methods;
  CRecordVector<CBind> _binds;
  bool _removeSfxBlock;
  bool _solidIsSpecified;
  bool _solid;
  bool _compressHeaders;
  bool _compressHeadersFull;
  bool _encryptHeaders;

  bool _copyMode;
  UINT32 _defaultDicSize;
  UINT32 _defaultAlgorithm;
  UINT32 _defaultFastBytes;
  bool _multiThread;

  HRESULT SetParam(COneMethodInfo &oneMethodInfo, const UString &name, const UString &value);
  HRESULT SetParams(COneMethodInfo &oneMethodInfo, const UString &srcString);

  HRESULT SetPassword(CCompressionMethodMode &methodMode,
      IArchiveUpdateCallback *updateCallback);

  HRESULT SetCompressionMethod(CCompressionMethodMode &method,
      CObjectVector<COneMethodInfo> &methodsInfo,
      bool multiThread);

  HRESULT SetCompressionMethod(
      CCompressionMethodMode &method,
      CCompressionMethodMode &headerMethod);

  #endif
  
  #ifndef _SFX

  CRecordVector<UINT64> _fileInfoPopIDs;
  void FillPopIDs();

  #endif


  void Init()
  {
    #ifndef EXTRACT_ONLY
    _removeSfxBlock = false;
    _solid = true;
    _solidIsSpecified = false;
    _compressHeaders = true;
    _compressHeadersFull = false;
    _encryptHeaders = false;
    _multiThread = false;
    _copyMode = false;
    _defaultDicSize = (1 << 20);
    _defaultAlgorithm = 1;
    _defaultFastBytes = 32;
    #endif
  }
};

}}

#endif