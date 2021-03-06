#ifndef Analysis_Core_TriggerObject_h
#define Analysis_Core_TriggerObject_h 1

// -*- C++ -*-
//
// Package:    Analysis/Core
// Class:      TriggerObject
//
/**\class TriggerObject TriggerObject.cc Analysis/Core/src/TriggerObject.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Rostyslav Shevchenko
//         Created:  Fri, 08 Oct 2015 17:56:18 GMT
//
//

// system include files
#include <memory>
//
// user include files
#include "Analysis/Core/interface/Candidate.h"
//
// class declaration
//

namespace analysis {
   namespace core {

      class TriggerObject : public Candidate {
         public:
            TriggerObject();
            TriggerObject(const float & pt, const float & eta, const float & phi, const float & e);
           ~TriggerObject();
           
	   //Gets
	   /// returns the type of the trigger object (L1mu, L1jet, hltmu, etc)
	   int type()          const;
	   
	   //Sets
	   //sets the type of the trigger object
	   void type(const int &);
	   
         protected:
           // ----------member data ---------------------------
	   ///type of the trigger object
	   int type_;
	   
            //
         private:
	   // ----------member data ---------------------------
      };
   }
}

#endif  // Analysis_Core_TriggerObject_h
