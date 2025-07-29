#!/usr/bin/env bash
set -euo pipefail

DATE="${1:-$(date +%F)}"          # 引数1があればその日付、なければ今日
OUTDIR="plots/${DATE}/test_macro"

# ROOT コマンドが見えるか（thisroot.sh が読まれているか）チェック
command -v root >/dev/null || { echo "[ERR] root not found. source thisroot.sh?"; exit 127; }

mkdir -p "$OUTDIR" results

# マクロをバッチ実行（画面なし）
root -l -b -q 'macros/draw_test.C("'"$OUTDIR"'" )'

# 出力確認＆サマリ表示
PNG="$OUTDIR/h_gaus.png"
PDF="$OUTDIR/h_gaus.pdf"
[[ -f "$PNG" && -f "$PDF" ]] || { echo "[ERR] output not found under $OUTDIR"; exit 1; }

SIZE=$(du -h "$PNG" | awk '{print $1}')
echo "[SUMMARY] $PNG ($SIZE)"
