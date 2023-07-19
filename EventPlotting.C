void ClearEvent(std::vector<double> nue_x, std::vector<double> nue_y, std::vector<double> nue_z, std::vector<double> numu_x, std::vector<double> numu_y, std::vector<double> numu_z,
  std::vector<double> e_x, std::vector<double> e_y, std::vector<double> e_z, std::vector<double> mu_x, std::vector<double> mu_y, std::vector<double> mu_z, std::vector<double> gamma_x, 
  std::vector<double> gamma_y, std::vector<double> gamma_z)
{
nue_x.clear();
nue_y.clear();
nue_z.clear();
numu_x.clear();
numu_y.clear();
numu_z.clear();
e_x.clear();
e_y.clear();
e_z.clear();
mu_x.clear();
mu_y.clear();
mu_z.clear();
gamma_x.clear();
gamma_y.clear();
gamma_z.clear();
}

void EventPlotting()
{

  string InputFile = "analysis/output0.root";
  TFile *f = new TFile(InputFile.c_str());
  TTree *tree = (TTree *)f->Get("event");
  TTree *tree_primary= (TTree *)f->Get("Primary");
  Int_t eventID, pdg;
  Double_t hitX_start, hitX_end, hitY_start, hitY_end, hitZ_start, hitZ_end, time_start, time_end, length, edep, PrimaryEnergy;

  tree->SetBranchAddress("eventID", &eventID);
  tree->SetBranchAddress("hit_start_x", &hitX_start);
  tree->SetBranchAddress("hit_start_y", &hitY_start);
  tree->SetBranchAddress("hit_start_z", &hitZ_start);
  tree->SetBranchAddress("hit_end_x", &hitX_end);
  tree->SetBranchAddress("hit_end_y", &hitY_end);
  tree->SetBranchAddress("hit_end_z", &hitZ_end);
  tree->SetBranchAddress("hit_start_t", &time_start);
  tree->SetBranchAddress("hit_end_t", &time_end);
  tree->SetBranchAddress("hit_length", &length);
  tree->SetBranchAddress("hit_energy_deposit", &edep);
  tree->SetBranchAddress("pdg", &pdg);

  int nEvents=100;

  for(int n = 0 ; n<nEvents; n++)
  {


    string eventID_str = "eventID=="+std::to_string(n);
    const char* cut_event_str = eventID_str.c_str();

    TCanvas *c1 = new TCanvas("c1", "c1", 1200, 1200);
    TCut cut_event= cut_event_str;
    TCut cut_enerydepo = "hit_energy_deposit>0";
    TCut cut_electron="abs(pdg)==11";
    TCut cut_muon="abs(pdg)==13";
    TCut cut_nue="abs(pdg)==12";
    TCut cut_numu="abs(pdg)==14";
    TCut cut_gamma="abs(pdg)==22";
    TCut cut_neutron="abs(pdg)==2112";
    TCut cut_proton="abs(pdg)==2212";
    TCut cut_alpha="abs(pdg)==1000020040";
    TCut cut_primary_neutrino="trackID==0";


    tree->Draw("hit_start_x:hit_start_z",cut_electron+cut_event+cut_enerydepo, "goff");
    TGraph *graph_electron = new TGraph(tree->GetSelectedRows(), tree->GetV2(), tree->GetV1());
    tree->Draw("hit_start_x:hit_start_z",cut_muon+cut_event+cut_enerydepo, "goff");
    TGraph *graph_muon = new TGraph(tree->GetSelectedRows(), tree->GetV2(), tree->GetV1());
    tree->Draw("hit_start_x:hit_start_z",cut_nue+cut_event+cut_primary_neutrino, "goff");
    TGraph *graph_nue = new TGraph(tree->GetSelectedRows(), tree->GetV2(), tree->GetV1());
    tree->Draw("hit_start_x:hit_start_z",cut_numu+cut_event+cut_primary_neutrino, "goff");
    TGraph *graph_numu = new TGraph(tree->GetSelectedRows(), tree->GetV2(), tree->GetV1());
    tree->Draw("hit_start_x:hit_start_z",cut_gamma+cut_event+cut_enerydepo, "goff");
    TGraph *graph_gamma = new TGraph(tree->GetSelectedRows(), tree->GetV2(), tree->GetV1());
    tree->Draw("hit_start_x:hit_start_z",cut_neutron+cut_event+cut_enerydepo, "goff");
    TGraph *graph_neutron = new TGraph(tree->GetSelectedRows(), tree->GetV2(), tree->GetV1());
    tree->Draw("hit_start_x:hit_start_z",cut_proton+cut_event+cut_enerydepo, "goff");
    TGraph *graph_proton = new TGraph(tree->GetSelectedRows(), tree->GetV2(), tree->GetV1());
    tree->Draw("hit_start_x:hit_start_z",cut_alpha+cut_event+cut_enerydepo, "goff");
    TGraph *graph_alpha = new TGraph(tree->GetSelectedRows(), tree->GetV2(), tree->GetV1());

    graph_electron->SetMarkerStyle(8);
    graph_electron->SetMarkerColor(7);
    graph_electron->SetMarkerSize(0.5);

    graph_muon->SetMarkerStyle(8);
    graph_muon->SetMarkerColor(1);
    graph_muon->SetMarkerSize(0.5);

    graph_nue->SetMarkerStyle(8);
    graph_nue->SetMarkerColor(3);
    graph_nue->SetMarkerSize(2);

    graph_numu->SetMarkerStyle(8);
    graph_numu->SetMarkerColor(4);
    graph_numu->SetMarkerSize(0.5);

    graph_gamma->SetMarkerStyle(8);
    graph_gamma->SetMarkerColor(95);
    graph_gamma->SetMarkerSize(0.5);

    graph_neutron->SetMarkerStyle(8);
    graph_neutron->SetMarkerColor(6);
    graph_neutron->SetMarkerSize(0.5);

    graph_proton->SetMarkerStyle(8);
    graph_proton->SetMarkerColor(9);
    graph_proton->SetMarkerSize(0.5);

    graph_alpha->SetMarkerStyle(8);
    graph_alpha->SetMarkerColor(12);
    graph_alpha->SetMarkerSize(0.5);

    auto legend = new TLegend(0.07,0.8,0.28,0.95);

    TMultiGraph *mg = new TMultiGraph();
    if(graph_electron->GetN()!=0)
    {
    mg->Add(graph_electron);
    legend->AddEntry(graph_electron,"electron","p");
    }
    if(graph_muon->GetN()!=0)
    {
    mg->Add(graph_muon);
    legend->AddEntry(graph_muon,"muon","p");
    }


    if(graph_nue->GetN()!=0)
    {
    mg->Add(graph_nue);
    legend->AddEntry(graph_nue,"nue","p");
    }


    if(graph_numu->GetN()!=0)
    {
    mg->Add(graph_numu);
    legend->AddEntry(graph_numu,"numu","p");
    }

    if(graph_gamma->GetN()!=0)
    {
    mg->Add(graph_gamma);
    legend->AddEntry(graph_gamma,"gamma","p");
    }

    if(graph_neutron->GetN()!=0)
    {
    mg->Add(graph_neutron);
    legend->AddEntry(graph_neutron,"neutron","p");
    }
    mg->Draw("AP");

    if(graph_proton->GetN()!=0)
    {
    mg->Add(graph_proton);
    legend->AddEntry(graph_proton,"proton","p");
    }

    if(graph_alpha->GetN()!=0)
    {
    mg->Add(graph_alpha);
    legend->AddEntry(graph_alpha,"alpha","p");
    }

    //mg->Draw("AP");

    //mg->GetYaxis()->SetRangeUser(-650,650);
    //mg->GetXaxis()->SetLimits(-1000,1000);
    //mg->GetYaxis()->SetRangeUser(-650,650);

    //legend->Draw();
    tree_primary->Draw("energy>>HISTOGRAMNAME", "pdg==12 || pdg==11");
    c1->Update();
    c1->Modified();
    c1->WaitPrimitive();
  }

}


