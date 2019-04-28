#include <iostream>
#include <fstream>
#include "TChain.h"
#include "TSystem.h"
#include "TString.h"
#include "TrackStudy.h"
#include "Track.h"
#include "PatHit.h"
#include "MCHit.h"
//#include "TSelector.h"
#include <TROOT.h>

int main(int argc, char* argv[]) {
  TString fileName = "$COMCHA_DIR/Upgrade-Tracking-v2/input/exampleTrackStudy.root";
  int minEvt = 0;
  int maxEvt = -1;
  TString outName  = "$COMCHA_DIR/Upgrade-Tracking-v2/output/Tracking-Test.root";

  if (argc > 1)
    {
      std::cout << "Reading arguments" << std::endl;
      fileName = argv[1];
      if (argc > 2)
        outName = argv[2];
      if (argc > 3)
        minEvt = std::atoi(argv[3]);
      if (argc > 4)
        maxEvt = std::atoi(argv[4]);      
    }
  std::cout << "INFO: Opening file: " << fileName << std::endl;
  std::cout << "INFO: Writing into: " << outName  << std::endl;
  std::cout << "INFO: Will process the events (" << minEvt << "," << maxEvt << ")" << std::endl;
  TChain ch2("PrClustersResidual/TrackStudy");
   
  //ch2.Add("./data/SciFi-Tuple-Debug_1000_Alessio.root");
  //ch2.Add("./data/V5/FTv5_NoNoise_Spillover_13104012_Residuals.root");
  //ch2.Add("./ToCopy/HitEfficiencies/FTv5_NoNoise_Spillover_13104012_Residuals.root");
  //ch2.Add("./ToCopy/CompareGeometries/FTv5_NoNoise_Spillover_13104012_Residuals.root");
  //ch2.Add("./data/BsPhiPhi_Brunel_PlotsGeo_V2_Spill_True_HybridSeed_True.root")
  //   ch2.Add("./Data/Trigger_BsPhiPhi_V5.root");
  int n = ch2.Add(fileName);
  if (n == 0)
    {
      std::cout << "ERROR: File " << fileName << " does not exist!" << std::endl;
      return 1;
    }
   TrackStudy *perfectSeeding1 = new TrackStudy();
   perfectSeeding1->OutputFileName = outName;
   perfectSeeding1->OutputTreeName = "TrackingTree";
   perfectSeeding1->Init( (TTree*)  &ch2);
   perfectSeeding1->Begin( (TTree*) &ch2);
   if (maxEvt == -1)
     maxEvt = ch2.GetEntries();
   Bool_t debug = false;
   std::cout<<"==========Will Process     "<<maxEvt - minEvt<<"      Tracks      "<<"     ===========    "<<std::endl;
   for (Int_t i = minEvt; i<maxEvt;i++){
     if( i %10000 == 0 ) std::cout<<"============="<<100.*(float)(i-minEvt)/(maxEvt-minEvt)<<"  % completed ========="<<std::endl;
     perfectSeeding1->Process(i,debug);
   }
   perfectSeeding1->Terminate();
   std::cout<<"Processed all tracks"<<std::endl;
   return 0;
}
