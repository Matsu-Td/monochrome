
/**
 * @file Mode_LightMap.h
 * @brief ライトマップ処理(暗転)
 *
 * @date 2020-09-24
 * @author 松尾忠彦
 */

#include "ModeBase.h"

class Mode_LightMap : public ModeBase
{
	using base = ModeBase;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

protected:
	// ライトのマスデータに円のスポットライトを入れる
	void SpotLight(int cx, int cy, int cr);

	static constexpr int DISP_W = 1920;    // 画面サイズ(横幅)
	static constexpr int DISP_H = 1080;    // 画面サイズ(縦幅)

	static constexpr int LIGHTSIZE_W = 2;  // ライトのマスサイズ(横幅)
	static constexpr int LIGHTSIZE_H = 2;  // ライトのマスサイズ(縦幅)

	static constexpr int LIGHTMAP_W = (DISP_W / LIGHTSIZE_W); // ライトのマス数(横)
	static constexpr int LIGHTMAP_H = (DISP_H / LIGHTSIZE_H); // ライトのマス数(縦)

	int	_mapLight[LIGHTMAP_W * LIGHTMAP_H];	// ライトのマスデータ
	int	_px, _py, _psize;                   // スポットライトの位置, サイズ
};