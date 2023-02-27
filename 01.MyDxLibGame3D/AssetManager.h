//-----------------------------------------------------------------------------
// @brief  アセット管理クラス.
//-----------------------------------------------------------------------------
#pragma once

#include <unordered_map>
#include <DxLib.h>
#undef LoadImage()
#pragma warning(disable:26812)  // enumの警告を消す
using namespace std;
// windowsのLoadImageを破壊するため

class AssetManager
{
public:
    enum ImageName  // 画像の取得に使用する列挙体
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

    enum ModelName  // 3Dモデルまたはアニメーションの取得に使用する列挙体
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

    static void LoadImage(ImageName name, const char* str)      // 事前に画像を読み込ませる関数
    {
        m_images.insert(make_pair(name, LoadGraph(str)));
    }

    static void LoadModel(ModelName name, const char* str)      // 事前に3Dモデルを読み込ませる関数
    {
        m_models.insert(make_pair(name, MV1LoadModel(str)));
    }

    static void Terminate()                                     // 取り込んだ画像と3Dモデルの解放処理
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

    static int UseImage(ImageName name)                         // 事前に読み込んだ画像を取得
    {
        return m_images[name];
    }

    static int UseModel(ModelName name)                         // 事前に読み込んだ3Dモデルを取得
    {
        return m_models[name];
    }

private:
    static unordered_map<ImageName, int> m_images;
    static unordered_map<ModelName, int> m_models;
};