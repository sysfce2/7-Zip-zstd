// UpdateProducer.h

#pragma once

#ifndef __UPDATEPRODUCER_H
#define __UPDATEPRODUCER_H

#include "UpdatePairInfo.h"

struct CUpdatePairInfo2
{
  bool OperationIsCompress;
  bool ExistInArchive;
  bool ExistOnDisk;
  bool IsAnti;
  int ArchiveItemIndex;
  int DirItemIndex;
};

typedef CObjectVector<CUpdatePairInfo2> CUpdatePairInfo2Vector;

void UpdateProduce(
      const CArchiveStyleDirItemInfoVector &aDirItems, 
      const CArchiveItemInfoVector &anArchiveItems, 
      const CUpdatePairInfoVector &anUpdatePairs,
      const NUpdateArchive::CActionSet &anActionSet,
      CUpdatePairInfo2Vector &anOperationChain);

#endif