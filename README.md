## 粒子法 C++ SDK
このプログラムは、鹿間（慶應義塾大学 藤代研究室 2014年入室-2017年卒業）が研究用に開発したプログラムをもとに、汎用的な粒子法プログラムとして開発しました。


### ディレクトリ構成

* リポジトリに含まれているディレクトリ
 * example - 使用例を示すためのかんたんなプログラムが入ってます
 * include - ヘッダファイル（\*.h, \*.hpp）が入っています
 * src - ソースファイル（\.cpp）が入っています
 * vendor - git のサブモジュールが入っています


* このプロジェクトをビルドすると生成されるディレクトリ
 * bin - exampleプログラムをコンパイルしたものがここに出力されます
 * lib - ライブラリファイル（\*.lib, \*.aなど）がここに出力されます


* その他
 * doc - Doxygen によって生成されたドキュメントはここに出力されます

### ビルドの仕方

* 必要なツール
 * cmake 2.7以降

cmakeの基本的な使い方を記述します。  
cmakeを通した後は、プラットフォームごとのビルドツールを使用してください

* Windows  
 WindowsではcmakeのGUIを利用してください

* Mac
 > $ cd path/to/directory  
 > $ mkdir build  
 > $ cd build  
 > $ cmake .. -G Xcode  

* Linux
  > $ cd path/to/directory  
  > $ mkdir build  
  > $ cd build  
  > $ cmake ..


## 依存ライブラリ
* Bullet Physics (物理エンジン)

## ライセンス
WTFPL  
好きにしやがれ
