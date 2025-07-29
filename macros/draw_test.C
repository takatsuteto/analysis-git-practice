#include <TCanvas.h>
#include <TH1F.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TRandom3.h>
#include <TString.h>

// 使い方: root -l -b -q 'macros/draw_test.C("plots/2025-07-29/test_macro")'
void draw_test(const char* outdir="plots/TEST") {
  gROOT->SetBatch(kTRUE);                // 画面を出さずに描画（バッチ）
  gSystem->mkdir(outdir, kTRUE);         // 出力フォルダを作成（あればスキップ）

  TH1F h("h", "Test Gaussian;ADC;Entries", 100, -5, 5);
  TRandom3 rng(42);                      // 乱数生成器（種42で再現性）
  for (int i = 0; i < 100000; ++i) h.Fill(rng.Gaus(0,1));  // 平均0,幅1のガウス

  TCanvas c("c","c",900,700);
  h.Draw();

  TString png = TString::Format("%s/h_gaus.png", outdir);
  TString pdf = TString::Format("%s/h_gaus.pdf", outdir);
  c.SaveAs(png);
  c.SaveAs(pdf);

  printf("[OK] Saved: %s and %s\n", png.Data(), pdf.Data());
}
