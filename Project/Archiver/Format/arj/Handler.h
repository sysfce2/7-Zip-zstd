// arj/Handler.h

#pragma once

#ifndef __ARJ_HANDLER_H
#define __ARJ_HANDLER_H

#include "../../Common/IArchiveHandler2.h"
#include "InEngine.h"
#include "Common/DynamicBuffer.h"
#include "../../../Compress/Interface/CompressInterface.h"

// {23170F69-40C1-278A-1000-0001100A0000}
DEFINE_GUID(CLSID_CarjHandler, 
  0x23170F69, 0x40C1, 0x278A, 0x10, 0x00, 0x00, 0x01, 0x10, 0x0A, 0x00, 0x00);

namespace NArchive {
namespace Narj {

class CHandler: 
  public IArchiveHandler200,
  public CComObjectRoot,
  public CComCoClass<CHandler,&CLSID_CarjHandler>
{
public:
BEGIN_COM_MAP(CHandler)
  COM_INTERFACE_ENTRY(IArchiveHandler200)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CHandler)

DECLARE_REGISTRY(CHandler, TEXT("SevenZip.FormatArj.1"), 
  TEXT("SevenZip.FormatArj"), 0, THREADFLAGS_APARTMENT)

  STDMETHOD(Open)(IInStream *aStream, 
      const UINT64 *aMaxCheckStartPosition,
      IOpenArchive2CallBack *anOpenArchiveCallBack);  
  STDMETHOD(Close)();  
  STDMETHOD(EnumProperties)(IEnumSTATPROPSTG **anEnumProperty);  
  STDMETHOD(GetNumberOfItems)(UINT32 *aNumItems);  
  STDMETHOD(GetProperty)(
      UINT32 anIndex, 
      PROPID aPropID,  
      PROPVARIANT *aValue);
  STDMETHOD(Extract)(const UINT32* anIndexes, UINT32 aNumItems, 
      INT32 aTestMode, IExtractCallback200 *anExtractCallBack);
  STDMETHOD(ExtractAllItems)(INT32 aTestMode, 
      IExtractCallback200 *anExtractCallBack);

  CHandler();
private:
  CItemInfoExVector m_Items;
  CComPtr<IInStream> m_Stream;
};

}}

#endif