
/**
 * @file Mode_LightMap.h
 * @brief ���C�g�}�b�v����(�Ó])
 *
 * @date 2020-09-24
 * @author �������F
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
	// ���C�g�̃}�X�f�[�^�ɉ~�̃X�|�b�g���C�g������
	void SpotLight(int cx, int cy, int cr);

	static constexpr int DISP_W = 1920;    // ��ʃT�C�Y(����)
	static constexpr int DISP_H = 1080;    // ��ʃT�C�Y(�c��)

	static constexpr int LIGHTSIZE_W = 2;  // ���C�g�̃}�X�T�C�Y(����)
	static constexpr int LIGHTSIZE_H = 2;  // ���C�g�̃}�X�T�C�Y(�c��)

	static constexpr int LIGHTMAP_W = (DISP_W / LIGHTSIZE_W); // ���C�g�̃}�X��(��)
	static constexpr int LIGHTMAP_H = (DISP_H / LIGHTSIZE_H); // ���C�g�̃}�X��(�c)

	int	_mapLight[LIGHTMAP_W * LIGHTMAP_H];	// ���C�g�̃}�X�f�[�^
	int	_px, _py, _psize;                   // �X�|�b�g���C�g�̈ʒu, �T�C�Y
};