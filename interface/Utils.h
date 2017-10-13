#ifndef Analysis_Core_Utils_h
#define Analysis_Core_Utils_h 1

namespace analysis {
   namespace core {

      struct FilterResults
      {
         int   total;
         int   filtered;
         float efficiency;
      };
      
      struct PDF
      {
         std::pair<int,int> id;
         std::pair<double,double> x;
      };
   }
}

#endif  // Analysis_Core_Utils_h
