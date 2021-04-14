
/**
 * @file ModeMelody.h
 * @brief �l�������m�F���
 *
 * @date 2020-09-24
 * @author �������F
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
	static constexpr int GROUND_Y = 507;              // �i�X�N���n�ʒu

	static constexpr int MELODY_TOTALNO = 6;          // ����\�ȃ����f�B�̂����瑍��
	static constexpr int INITIAL_POS = 450;           // �����f�B�̂�����\�������ʒu
	static constexpr int VERTICAL_WIDTH = 50;         // �����A�j���[�V������
	const int MELODY_ANIM_SPD[MELODY_TOTALNO] = { 240,120,180,150,210,90 };  // �����A�j���[�V�������x(����)

	const int PIANO_POS_X[7] = { 373,569,766,961,1152,1344,1537 };   // �s�A�m�u���b�N�\�� X���W
	static constexpr int PIANO_POS_Y = 580;                          // �s�A�m�u���b�N�\�� Y���W

	static constexpr int MODORU_POS_X = 40;                          //�u���ǂ�v�\�� X���W
	static constexpr int MODORU_POS_Y = 960;                         //�u���ǂ�v�\�� Y���W

protected:	
	int	_bg;          // �w�i	
	int	_cgModoru;    // ���ǂ�
	int _cgPiano[4];  // �s�A�m�u���b�N
	int	_cgNasu[4];   // �i�X�N
	int _cgMelody[2]; // �����f�B�̂�����

	int _x, _y;       // �i�X�N���W
	int _sinCnt;      // �����A�j���[�V�����p�J�E���g
	int _g;           // �d�͉����x
	int _cgNum;       // �摜�̔ԍ�
	int _melx[MELODY_TOTALNO] = { 619,816,1011,1202,1394,1587 };   // �����f�B�̂����� X���W
	int _mely[MELODY_TOTALNO] = { 0 };                             // �����f�B�̂����� Y���W
};