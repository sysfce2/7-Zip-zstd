// Tar/Handler.h

#pragma once

#ifndef __TAR_HANDLER_H
#define __TAR_HANDLER_H

#include "Common/MyCom.h"
#include "../IArchive.h"

#include "TarItem.h"

namespace NArchive {
namespace NTar {

class CHandler: 
  public IInArchive,
  public IOutArchive,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP2(
    IInArchive,
    IOutArchive
  )

  STDMETHOD(Open)(IInStream *stream, 
      const UINT64 *maxCheckStartPosition,
      IArchiveOpenCallback *openArchiveCallback);  
  STDMETHOD(Close)();  
  STDMETHOD(GetNumberOfItems)(UINT32 *numItems);  
  STDMETHOD(GetProperty)(UINT32 index, PROPID propID, PROPVARIANT *value);
  STDMETHOD(Extract)(const UINT32* indices, UINT32 numItems, 
      INT32 testMode, IArchiveExtractCallback *extractCallback);
  
  STDMETHOD(GetArchiveProperty)(PROPID propID, PROPVARIANT *value);

  STDMETHOD(GetNumberOfProperties)(UINT32 *numProperties);  
  STDMETHOD(GetPropertyInfo)(UINT32 index,     
      BSTR *name, PROPID *propID, VARTYPE *varType);

  STDMETHOD(GetNumberOfArchiveProperties)(UINT32 *numProperties);  
  STDMETHOD(GetArchivePropertyInfo)(UINT32 index,     
      BSTR *name, PROPID *propID, VARTYPE *varType);

  // IOutArchive
  STDMETHOD(UpdateItems)(IOutStream *outStream, UINT32 numItems,
      IArchiveUpdateCallback *updateCallback);
  STDMETHOD(GetFileTimeType)(UINT32 *type);  

private:
  CObjectVector<CItemEx> _items;
  CMyComPtr<IInStream> _inStream;
};

}}

#endif