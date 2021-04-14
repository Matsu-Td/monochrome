
/**
 * @file ModeMelody.h
 * @brief 獲得音符確認画面
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include	"ModeBase.h"

class ModeMelody : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

private:
	static constexpr int GROUND_Y = 507;              // ナス君着地位置

	static constexpr int MELODY_TOTALNO = 6;          // 入手可能なメロディのかけら総数
	static constexpr int INITIAL_POS = 450;           // メロディのかけら表示初期位置
	static constexpr int VERTICAL_WIDTH = 50;         // 垂直アニメーション幅
	const int MELODY_ANIM_SPD[MELODY_TOTALNO] = { 240,120,180,150,210,90 };  // 垂直アニメーション速度(分母)

	const int PIANO_POS_X[7] = { 373,569,766,961,1152,1344,1537 };   // ピアノブロック表示 X座標
	static constexpr int PIANO_POS_Y = 580;                          // ピアノブロック表示 Y座標

	static constexpr int MODORU_POS_X = 40;                          //「もどる」表示 X座標
	static constexpr int MODORU_POS_Y = 960;                         //「もどる」表示 Y座標

protected:	
	int	_bg;          // 背景	
	int	_cgModoru;    // もどる
	int _cgPiano[4];  // ピアノブロック
	int	_cgNasu[4];   // ナス君
	int _cgMelody[2]; // メロディのかけら

	int _x, _y;       // ナス君座標
	int _sinCnt;      // 垂直アニメーション用カウント
	int _g;           // 重力加速度
	int _cgNum;       // 画像の番号
	int _melx[MELODY_TOTALNO] = { 619,816,1011,1202,1394,1587 };   // メロディのかけら X座標
	int _mely[MELODY_TOTALNO] = { 0 };                             // メロディのかけら Y座標
};