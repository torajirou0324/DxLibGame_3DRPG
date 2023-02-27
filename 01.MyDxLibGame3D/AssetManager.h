//-----------------------------------------------------------------------------
// @brief  �A�Z�b�g�Ǘ��N���X.
//-----------------------------------------------------------------------------
#pragma once

#include <unordered_map>
#include <DxLib.h>
#undef LoadImage()
#pragma warning(disable:26812)  // enum�̌x��������
using namespace std;
// windows��LoadImage��j�󂷂邽��

class AssetManager
{
public:
    enum ImageName  // �摜�̎擾�Ɏg�p����񋓑�
    {
        Title,
        RightArrow,
        DownArrow,
        BlackWindow,
        CommandWindowWhite,
        CommandWindowBlack,
        StatusWindow,
        MapTile,
        PlayerTexture1,
        PlayerTexture2,
        PlayerTexture3,
        PlayerTexture4,
        DeamonTexture1,
        DeamonTexture2,
        DeamonTexture3
    };

    enum ModelName  // 3D���f���܂��̓A�j���[�V�����̎擾�Ɏg�p����񋓑�
    {
        Field,
        Wall,
        Player,
        Deamon,
        IconRed,
        IconBlue,
        IconGreen,
        AnimAttack,
        AnimDamage,
        AnimDeath,
        AnimIdle,
        AnimWalk
    };

    static void LoadImage(ImageName name, const char* str)      // ���O�ɉ摜��ǂݍ��܂���֐�
    {
        m_images.insert(make_pair(name, LoadGraph(str)));
    }

    static void LoadModel(ModelName name, const char* str)      // ���O��3D���f����ǂݍ��܂���֐�
    {
        m_models.insert(make_pair(name, MV1LoadModel(str)));
    }

    static void Terminate()                                     // ��荞�񂾉摜��3D���f���̉������
    {
        for (const auto& it : m_images)
        {
            DeleteGraph(it.second);
        }

        for (const auto& it : m_models)
        {
            MV1DeleteModel(it.second);
        }

        m_images.clear();
        m_models.clear();
    }

    static int UseImage(ImageName name)                         // ���O�ɓǂݍ��񂾉摜���擾
    {
        return m_images[name];
    }

    static int UseModel(ModelName name)                         // ���O�ɓǂݍ���3D���f�����擾
    {
        return m_models[name];
    }

private:
    static unordered_map<ImageName, int> m_images;
    static unordered_map<ModelName, int> m_models;
};