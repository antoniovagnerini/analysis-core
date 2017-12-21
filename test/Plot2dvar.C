#include "tdrstyle.C"

void Plot2dvar(string var_)
{

  // std::string var = "n_ptmin20_btagsel_phivseta";
  std::string var = var_;
  //  setTDRStyle();

  gStyle->SetOptStat(0);

  std::vector<std::string> eras;
  eras.push_back("C");
  eras.push_back("D");
  eras.push_back("E-v1");
  eras.push_back("E-v2");
  eras.push_back("F");

  float lumi = 5.0 ;// in fb-1
  std::vector<float> era_lumis = {9.787, 4.324, 4.275, 5.111, 4.530};  //eras C,D,Ev1,Ev2,F  map better
  std::vector<float> era_sf ;
  for( float era_lumi : era_lumis ) {  era_sf.push_back( lumi/era_lumi ) ; }

  TFile * f[20]; // signal

  for ( size_t e = 0; e < eras.size(); e++  )
   {
     f[e] = new TFile(Form("ROOTFILES/histograms_2017%s.root",eras[e].c_str()),"OLD");
  
     TH2F * hvar = (TH2F*) f[e]->Get(var.c_str());  
     std::cout << var << " "  << var.length() <<std::endl; 
     
     hvar-> Scale(era_sf[e]);
     //     hvar-> RebinY(2);

     TCanvas *c1 = new TCanvas("c1", "c1",2067,115,1310,869); //2067,113
     c1->SetFillColor(0);
     c1->SetBorderMode(0);
     c1->SetBorderSize(2);
     c1->SetTheta(89.88808);
     c1->SetPhi(-0.06576451);
     c1->SetFrameBorderMode(0);
   
     hvar -> GetXaxis()->SetTitle("Eta");
     hvar -> GetYaxis()->SetTitle("Phi");
     hvar -> GetYaxis()->SetTitleOffset(1.05);
     hvar -> GetXaxis()->SetRangeUser(-2.3,2.3);
     hvar -> GetYaxis()->SetRangeUser(-3.14,3.14);
     hvar ->Draw("colz");
   

     c1 -> SaveAs(("PLOTS/"+ var + eras[e] + ".png").c_str());

     f[e]-> Close();
   }
   
  

}
