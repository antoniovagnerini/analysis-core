#include "boost/program_options.hpp"
#include "boost/algorithm/string.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "TFile.h" 
#include "TFileCollection.h"
#include "TChain.h"
#include "TH1.h" 

#include "Analysis/Core/interface/Analysis.h"
#include "Analysis/Core/bin/macro_config.h"

using namespace std;
using namespace analysis;
using namespace analysis::core;

// =============================================================================================   
int main(int argc, char * argv[])
{
     
   if ( macro_config(argc, argv) != 0 ) return -1;
   
   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
  
   // Input files list
   Analysis analysis(inputlist_);
 
   analysis.addTree<Muon>("Muons","MssmHbb/Events/slimmedMuons");
   for ( auto & obj : triggerObjectsMuons_ )
       analysis.addTree<TriggerObject> (obj,Form("MssmHbb/Events/slimmedPatTrigger/%s",obj.c_str()));
       
   analysis.triggerResults("MssmHbb/Events/TriggerResults");
   if( !isMC_ ) analysis.processJsonFile(json_);
 
   // Jets --------------------------------------------------------------------------------------
   // h1["n_MuFired"]            = new TH1F("n_MuFired" ,         "" , 30, 0 ,30 );      // # jets 
   // h1["n_MuPFFired"]          = new TH1F("n_MuPFFired" ,       "" , 30, 0 ,30 );      // # jets 
 
   int nsel[6] = {};
   
   // Analysis of events
   std::cout << "This analysis has " << analysis.size() << " events" << std::endl;
      
   for ( int i = 0 ; i < analysis.size()  ; ++i )
   { 
      if ( i > 0 && i%100000==0 ) std::cout << i << "  events processed! " << std::endl;
      analysis.event(i);

      if (! isMC_ )
      {
         if (!analysis.selectJson() ) continue; // To use only goodJSonFiles
      }
    
      //  TRIGGERED EVTs   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      int triggerFired = analysis.triggerResult(hltPath_); 
      int triggerFired2 = analysis.triggerResult("HLT_PFJet40_v");
      //      if ( !triggerFired ) continue;
      //++nsel[0];
      
      // auto slimmedMuons = analysis.collection<Muon>("Muons");
      // analysis.match<Muon,TriggerObject>("Muons",triggerObjectsMuons_,0.5);
           
      
      //if ( !triggerFired2 ) continue;
      //++nsel[1];
      if ( triggerFired ) ++nsel[0];
      if ( triggerFired2 ) ++nsel[1];
      if ( triggerFired && triggerFired2 ) ++nsel[2];

 
    } //end event loop

   // h1["n_MuFired"]-> Fill(nsel[0]);
   // h1["n_MuPFFired"]-> Fill(nsel[1]); 
   

// PRINT OUTS  ============================================================================================ 
   
 
   printf ("%10s  %10s \n", std::string("Trigger fired").c_str(), std::string("# events").c_str() ); 
   printf ("%10s  %10d \n", std::string("HLT_Mu8_v ").c_str(), nsel[0] );
   printf ("%10s  %10d \n", std::string("HLT_PFJet40_v").c_str(), nsel[1]  );
   printf ("%10s  %10d \n", std::string("HLT_Mu8_PFJet40_v").c_str(), nsel[2]  ); 



} //end main

