#pragma once
#include <mutex>
#include <vector>
#include <map>

struct ActionHeader {
	float version;			// ̧�ق��ް�ޮ�
	std::string fileName;	// ̧�ٖ�
	int actCnt;				// ����݂̎�ސ� �����̌�������forٰ�߂��ı���݂��Ƃɂ܂Ƃ߂�
};

struct ActionData {
	VECTOR2 rect;			// �����J�n�ʒu
	int width;				// 1�ς̉摜�̉��̒���
	int height;				// 1�ς̉摜�̏c�̒���
	VECTOR2 center;			// 1�ς̉摜�̒��S�_
	int duration;			// ��Ұ��݂̺ϊԊu
	int actRcType;			// �����蔻��p��`�̎��
	VECTOR2 actRect;		// �����蔻��p��`�̊J�n�ʒu
	int actRcWidth;			// �����蔻��p��`�̉��̒���
	int actRcHeight;		// �����蔻��p��`�̏c�̒���
};

class VECTOR2;
using VEC_INT = std::vector<int>;
using VEC_ACT = std::vector<ActionData>;

//�Z�k��`
#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X))

class ImageMng
{
public:
	static ImageMng &GetInstance(void)
	{
		static ImageMng s_instance;
		return s_instance;
	}

	//LoadGraph�p
	const VEC_INT& GetID(std::string f_name);
	//LoadDivGraph�Ή�
	const VEC_INT& GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt);

	// �޲���ް��̓ǂݍ���
	void ReadGraph(void);

private:
	ImageMng();
	~ImageMng();

	std::map<std::string, VEC_INT> imageMap;
	ActionHeader header;
	std::map<std::string, VEC_ACT> data;
};