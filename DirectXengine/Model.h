#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <DirectXTex.h>
#include <d3dx12.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "Mesh.h"

//ノード
struct Node
{
	//名前
	std::string name;
	//ローカルスケール
	DirectX::XMVECTOR scaling = { 1, 1, 1, 0 };
	//ローカル回転角
	DirectX::XMVECTOR rotation = { 0, 0, 0, 0 };
	//ローカル移動
	DirectX::XMVECTOR translation = { 0, 0, 0, 1 };
	//ローカル変形行列
	DirectX::XMMATRIX transform;
	//グローバル変形行列
	DirectX::XMMATRIX globalTransform;
	//親ノード
	Node* parent = nullptr;
};

//モデル
class Model
{
private://エイリアス
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScratchImage = DirectX::ScratchImage;

	//std::を省略
	using string = std::string;
	template <class T> using vector = std::vector<T>;

public://サブクラス
	//頂点データ構造体
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos;//XYZ座標
		DirectX::XMFLOAT3 normal;//法線ベクトル
		DirectX::XMFLOAT2 uv;//UV座標
	};

public://フレンドクラス
	friend class FbxLoader;

private:
	static const std::string baseDirectory;

private://静的メンバ変数
	static ID3D12Device* dev;//デバイス
	static UINT descriptorHandleIncrementSize;//デスクリプタサイズ

public://静的メンバ関数
	static void StaticInitialize(ID3D12Device* dev);//静的初期化
	static Model* CreateFromOBJ(const std::string& modelname);//OBJファイルからメッシュ生成

public://メンバ関数
	~Model();//デストラクタ
	void Initialize(const std::string& modelname);//初期化処理
	void Draw(ID3D12GraphicsCommandList* cmdList);//描画処理

private://メンバ変数
	std::string name;//名前
	std::vector<Node> nodes;//ノード配列
	Node* meshNode = nullptr;//メッシュを持つノード
	std::vector<VertexPosNormalUv> vertices;//頂点データ配列
	std::vector<unsigned short> indices;//頂点インデックス配列
	DirectX::XMFLOAT3 ambient = { 1, 1, 1 };//アンビエント係数
	DirectX::XMFLOAT3 diffuse = { 1, 1, 1 };//ディフューズ係数
	DirectX::TexMetadata metadata = {};//テクスチャメタデータ
	DirectX::ScratchImage scratchImg = {};//スクラッチイメージ

	std::vector<Mesh*> meshes;//メッシュコンテナ
	std::unordered_map<std::string, Material*> materials;//マテリアルコンテナ
	Material* defaultMaterial = nullptr;//デフォルトマテリアル
	ComPtr<ID3D12DescriptorHeap> descHeap;//デスクリプタヒープ

private://メンバ関数
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);//マテリアル読み込み
	void AddMaterial(Material* material);//マテリアル登録
	void CreateDescriptorHeap();//デスクリプタヒープの生成
	void LoadTextures();//テクスチャ読み込み

};