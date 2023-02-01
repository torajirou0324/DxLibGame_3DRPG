//-----------------------------------------------------------------------------
// @brief  アセット管理クラス.
//-----------------------------------------------------------------------------
#include "AssetManager.h"

unordered_map<AssetManager::ImageName, int> AssetManager::m_images;
unordered_map<AssetManager::ModelName, int> AssetManager::m_models;