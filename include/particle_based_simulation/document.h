//
//  document.h
//  ParticleBasedSimulation
//
//  Created by Shuto Shikama on 2017/01/31.
//
//

#ifndef document_h
#define document_h

/**
 @mainpage
 
 # 粒子法搭載シミュレータ
 Bullet Physics SDK をベースにしたシミュレータです.

 ## ユーザへ
 Bullet Physics に精通しているとなお入門しやすいでしょう. 
 Bullet Physics HP(http://bulletphysics.org/wordpress/)最終アクセス1/31\n
 fj::CollisionObject を継承しているクラスがシミュレーション可能な物体です.
 
 使い方の概要
 - 必要なアルゴリズムのインスタンス化
 - インスタンスがもつワールドへの物体登録
 - fj::Algorithm::stepSimulation() をよぶ

 ## 開発者へ
 C++11で記述されています.\n
 独自の粒子法アルゴリズムを追加したい場合, fj::Algorhtm を継承したクラスを作成してください.
 このとき, テンプレート引数に独自アルゴリズムで必要なパラメタを指定できます. \n
 このシステムの内部では, すべての球体は粒子法で使用する物体だとみなされます.
 プリミティブとして球体を使用することはできません.
 */

#endif /* document_h */
