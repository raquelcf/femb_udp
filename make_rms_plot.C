{
  FILE *fp;
  int i,n;
  int numChars = 0;
  int numLines = 0;
  char buff[512];
  size_t num;
  
  float last_max_Xvalue = -9999.;
  float max_Xvalue;
  float last_min_Xvalue = 9999.;
  float min_Xvalue;
  
  float last_max_Yvalue = -9999.;
  float max_Yvalue;
  float last_min_Yvalue = 9999.;
  float min_Yvalue;
  
  char * filename = "rmsdata.txt";
  fp = fopen(filename,"r");
  if (fp == 0)
  {
    printf("Unable to open file. Terminating...\n");
    exit(1);
  }
  while ((num = fread(buff,1,512,fp)) > 0)
  {
    for (i=0;i<num;++i)
    {
      if (buff[i] == '\n')
      {
      	++numLines;
      }
    }
  }
  fclose(fp);
  
  const int numL = numLines;
  float x1[numL];
  float x2[numL];
  float x[numL];
  float y[numL];
  float xErr[numL];
  float yErr[numL];
  
  fp = fopen(filename,"r");
  for(i=0;i<numL;i++)
  {
    fscanf(fp,"%f %f %f %f",&x1[i],&x2[i],&y[i],&yErr[i]);
    x[i] = 16*x1[i]+x2[i];
    xErr[i] = 0.5;
  
    max_Xvalue = (x[i] >= last_max_Xvalue) ? x[i] : last_max_Xvalue;
    last_max_Xvalue=max_Xvalue;
    min_Xvalue = (x[i] <= last_min_Xvalue) ? x[i] : last_min_Xvalue;
    last_min_Xvalue=min_Xvalue;
  
    max_Yvalue = (y[i] >= last_max_Yvalue) ? y[i] : last_max_Yvalue;
    last_max_Yvalue=max_Yvalue;
    min_Yvalue = (y[i] <= last_min_Yvalue) ? y[i] : last_min_Yvalue;
    last_min_Yvalue=min_Yvalue;
  }
  fclose(fp);

  TCanvas *c = new TCanvas("","",1600,400);
  c->Range(min_Xvalue-0.5,0.0,max_Xvalue+0.5,1.5*max_Yvalue);
  c->cd();
  gStyle->SetOptStat(0);

  //TGraph* g = new TGraph(numL,x,y);  
  TGraphErrors* g = new TGraphErrors(numL,x,y,xErr,yErr);  
  g->SetMarkerStyle(21);
  g->SetMarkerSize(0.5);
  g->SetMarkerColor(kBlue);
  g->GetHistogram()->SetTitle("RMS vs. Channel Number");
  g->GetHistogram()->GetXaxis()->SetTitle("Channel Number");
  g->GetHistogram()->GetXaxis()->SetTitleSize(0.04);
  g->GetHistogram()->GetYaxis()->SetTitle("RMS");
  g->GetHistogram()->GetYaxis()->SetTitleSize(0.05);
  g->GetHistogram()->GetYaxis()->SetTitleOffset(0.3);
  g->GetHistogram()->GetXaxis()->SetRangeUser(min_Xvalue-0.5,max_Xvalue+0.5);
  g->GetHistogram()->GetYaxis()->SetRangeUser(0.0,1.5*max_Yvalue);
  g->Draw("ALP");

  TLine* line1 = new TLine(15.5,0.0,15.5,1.5*max_Yvalue);
  line1->SetLineColor(kRed);
  line1->SetLineStyle(2);
  line1->Draw("same");

  TLine* line2 = new TLine(31.5,0.0,31.5,1.5*max_Yvalue);
  line2->SetLineColor(kRed);
  line2->SetLineStyle(2);
  line2->Draw("same");

  TLine* line3 = new TLine(47.5,0.0,47.5,1.5*max_Yvalue);
  line3->SetLineColor(kRed);
  line3->SetLineStyle(2);
  line3->Draw("same");

  TLine* line4 = new TLine(63.5,0.0,63.5,1.5*max_Yvalue);
  line4->SetLineColor(kRed);
  line4->SetLineStyle(2);
  line4->Draw("same");

  TLine* line5 = new TLine(79.5,0.0,79.5,1.5*max_Yvalue);
  line5->SetLineColor(kRed);
  line5->SetLineStyle(2);
  line5->Draw("same");

  TLine* line6 = new TLine(95.5,0.0,95.5,1.5*max_Yvalue);
  line6->SetLineColor(kRed);
  line6->SetLineStyle(2);
  line6->Draw("same");

  TLine* line7 = new TLine(111.5,0.0,111.5,1.5*max_Yvalue);
  line7->SetLineColor(kRed);
  line7->SetLineStyle(2);
  line7->Draw("same");

  TPaveLabel *label1 = new TPaveLabel(4.25, 1.3*max_Yvalue, 10.75, 1.45*max_Yvalue,"ASIC 0");
  label1->SetFillColor(kWhite);
  label1->Draw("same");

  TPaveLabel *label2 = new TPaveLabel(20.25, 1.3*max_Yvalue, 26.75, 1.45*max_Yvalue,"ASIC 1");
  label2->SetFillColor(kWhite);
  label2->Draw("same");

  TPaveLabel *label3 = new TPaveLabel(36.25, 1.3*max_Yvalue, 42.75, 1.45*max_Yvalue,"ASIC 2");
  label3->SetFillColor(kWhite);
  label3->Draw("same");

  TPaveLabel *label4 = new TPaveLabel(52.25, 1.3*max_Yvalue, 58.75, 1.45*max_Yvalue,"ASIC 3");
  label4->SetFillColor(kWhite);
  label4->Draw("same");

  TPaveLabel *label5 = new TPaveLabel(68.25, 1.3*max_Yvalue, 74.75, 1.45*max_Yvalue,"ASIC 4");
  label5->SetFillColor(kWhite);
  label5->Draw("same");

  TPaveLabel *label6 = new TPaveLabel(84.25, 1.3*max_Yvalue, 90.75, 1.45*max_Yvalue,"ASIC 5");
  label6->SetFillColor(kWhite);
  label6->Draw("same");

  TPaveLabel *label7 = new TPaveLabel(100.25, 1.3*max_Yvalue, 106.75, 1.45*max_Yvalue,"ASIC 6");
  label7->SetFillColor(kWhite);
  label7->Draw("same");

  TPaveLabel *label8 = new TPaveLabel(116.25, 1.3*max_Yvalue, 122.75, 1.45*max_Yvalue,"ASIC 7");
  label8->SetFillColor(kWhite);
  label8->Draw("same");

  c->SaveAs("rms_plot.png");

  return 0;
}
