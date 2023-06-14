<img width="2416" alt="flow_chart" src="https://github.com/uminomae/minirt1st/assets/101631407/2adfea34-8910-479b-972b-4bf15dec363c">
<img width="1241" alt="shadow" src="https://github.com/uminomae/minirt1st/assets/101631407/cb976432-5b11-4cdb-9962-0c6d3c2d356d">
<img width="1568" alt="スクリーンショット 2023-06-14 11 14 13" src="https://github.com/uminomae/minirt1st/assets/101631407/08c1f87a-8c8d-4920-b37e-2a5a8dcda5eb">
# minirt1st

# TEST
## info
1. 場所: test/
1. 実行方法: make t
## Sample
1. sample_picture.rt mandatory 機能確認用 make sp
1. sample_move.rt bonus key&mouse hook用 make sm


## 手動チェック
### 1.	並列処理の確認方法　マウス・key操作
1. シングルスレッド処理:　マウスのクリックor右クリック
1. マルチスレッド(pthread = 36)処理:　keyの "u" or "d" 
## NG Case
make n
### NG generally
1. test1 識別子が違う(spc)	Wrong identifier.
1. test2 スペース以外の文字で区切り(tab文字)	The number of values set is wrong.
1. test3 数字以外の文字(a)	An incorrect non-numeric value was detected.
1. test4 .rt拡張子のディレクトリ	Opening a directory. Or missing value.
1. test5 球のz位置が近い	Shape z position too close.
1. test6 円柱のz位置が近い	Shape z position too close.
1. test7 カメラのz位置が原点に近い	Camera z position too close.
1. test8 lightが球の中にある
### NG id_dup
1. test1 id Aが2回	Duplicate identifier.
1. test2 id Cが2回	Duplicate identifier.
1. test3 id Lが2回	Duplicate identifier.
### NG missing
1. test1 カメラ無し	Missing value.
1. test2 ライト無し	Missing value.
1. test3 環境光無し	Missing value.
1. test4 何もないファイル	Opening a directory. Or missing value.
1. test5 カラーが欠けている	The number of values set is wrong.
### NG out_of_range
1. test1 fovが大きすぎる(180.1)	fov is out of range.
1. test2 fovがマイナス(0.1)	fov is out of range.
1. test3 orientation vector が -1.0 以下(-1.01)	The camera direction values are wrong.
1. test4 orientation vector が　1.0 以上(1.01)	The camera direction values are wrong.
1. test5 lightのratioがマイナス(-0.01)	The light ratio setting values are wrong.
1. test6 カラーが255以上(256)	The rgb values are wrong.
1. test7 カラーがマイナス(-1)	The rgb values are wrong.
1. test8 ambientのratioが1.0以上(1.1)	The light ratio setting values are wrong.
1. test9 planeの法線がnormalizeされていない(norm!=1)	Not normalized.
1. test10 カメラの視線方向がnormalizeされていない。(norm!=1)	Not normalized.
### NG test.sh
1. test_rt 1 test/rt_file.rts	Please enter a file name ending in ".rt".
1. test_rt 2 test/rt_file.rd	Please enter a file name ending in ".rt".
1. test_rt 3 test/.rd	Please enter a file name ending in ".rt".
1. test_rt 4 test/filenamert	Please enter a file name ending in ".rt".
1. test_rt 5 test/filename.rt	open(): No such file or directory
1. test_rt 6 </dev/null	Please enter the file name.
1. test_rt 7 test/ng/.rt	Opening a directory. Or missing value.
1. test_rt 8 test/permission.rt	open(): No such file or directory
## OK Case
### OK camera　
make ocm
1. test1 fovが0
1. test2 fovが180
1. test3 カメラが床と同じ位置　0, 0, 0　※床が表示されない
1. test4 カメラと光源が同じ位置
1. test5 光源が原点
1. test6 カメラが床より下&&光源が床より上　※背景色と環境光の出力
1. test7 カメラ視線方向が真下 0, -1, 0
1. test8 カメラ視線方向が真上 0, 1, 0　※背景色と環境光の物体の出力
1. test9 カメラが物体の逆方向を見てる　0, 0, -1　※物体がない方向を見てる
1. test10 斜めの場合　0, 0.99, 0.01
### OK sphere
make osp
1. test1  複数ライト
1. test2  カメラ位置・方向 = 直上から下方向
1. test3  ライト色違い
1. test4  複数オブジェクト 
1. test5  複数オブジェクト 宙に浮いている
1. test6  複数オブジェクト 端の方が大きくなる視野角による歪み C 0,0,-5 0,0,1 120
1. test7  複数オブジェクト 等間隔
### OK plane
make opl
1. test1 単一ライト
1. test2 複数オブジェクト
1. test3 ライト色違い
### OK cylinder
make ocy
1. test1 単一光源　RED255
1. test2 単一光源　GREEN255
1. test3 単一光源　BLUE255
1. test4 複数カラー光源
1. test5 複数の円柱
1. test6 カメラ位置・方向 = 直上から下方向
### OK other
make oo
1. test1 spaceだけのラインは改行だけがあると解釈
1. test2 ファイルの先頭、途中、末尾に複数行の改行がある
1. test3 各パラメーターの順番がバラバラ
1. test4 1つのlightが球の中にあり、他に光源（赤）がある場合
1. test5 ライトが平面上にある
1. test6 ファイルの最後に改行がない
1. test7 オブジェクトが何もない ※正常挙動=背景色だけ表示される
1. test8 identiferの前にスペースがある
