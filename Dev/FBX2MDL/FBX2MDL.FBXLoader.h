
#include "FBX2MDL.Base.h"
#include "FBX2MDL.Mesh.h"

namespace FBX2MDL
{
	class FBXLoader
	{
		struct FbxWeight
		{
			float	Weight;
			int32_t	Index;

			FbxWeight()
				: Weight(0.0f)
				, Index(0x00)
			{
			}

			bool operator () (const FbxWeight& lhs, const FbxWeight& rhs)
			{
				return lhs.Weight > rhs.Weight;
			}
		};

		struct FbxVertexWeight
		{
			std::vector<FbxWeight> Data;
			int32_t Indexes[4];
			uint8_t Weights[4];

			FbxVertexWeight()
			{
				Indexes[0] = 0;
				Indexes[1] = 0;
				Indexes[2] = 0;
				Indexes[3] = 0;

				Weights[0] = 255;
				Weights[1] = 0;
				Weights[2] = 0;
				Weights[3] = 0;
			}
		};

		struct FbxFace
		{
			std::vector<Vertex> Vertecies;
			int32_t MaterialIndex;
		};

	private:

		ace::Vector3DF LoadPosition(FbxMesh* fbxMesh, int32_t ctrlPointIndex);
		ace::Vector3DF LoadNormal(FbxLayerElementNormal* normals, int32_t vertexID, int32_t ctrlPointIndex);
		ace::Vector2DF LoadUV(FbxMesh* fbxMesh, FbxLayerElementUV* uvs, int32_t vertexID, int32_t ctrlPointIndex, int32_t polygonIndex, int32_t polygonPointIndex);
		ace::Color LoadVertexColor(FbxMesh* fbxMesh, FbxLayerElementVertexColor* colors, int32_t vertexID, int32_t ctrlPointIndex, int32_t polygonIndex, int32_t polygonPointIndex);

		void LoadSkin(FbxMesh* fbxMesh, std::vector<BoneConnector>& boneConnectors, std::vector<FbxVertexWeight>& weights);
		void LoadMaterial(FbxMesh* fbxMesh, FbxLayerElementMaterial* materials, std::vector<Material>& dst);

		std::shared_ptr<Mesh> LoadMesh(FbxMesh* fbxMesh);

		std::shared_ptr<Node> LoadHierarchy(std::shared_ptr<Node> parent, FbxNode* fbxNode, FbxManager* fbxManager);

		ace::Matrix44 CalcMatrix(ace::eRotationOrder order, float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);

		void LoadAnimationSource(FbxAnimStack* fbxAnimStack, FbxNode* fbxRootNode, AnimationSource &animationSource);
		void LoadCurve(FbxNode* fbxNode, FbxAnimLayer* fbxAnimLayer, AnimationSource &animationSource);
		void LoadCurve(ace::astring target, FbxAnimCurve* curve, AnimationSource &animationSource);
	public:

		std::shared_ptr<Scene> LoadScene(FbxScene* fbxScene, FbxManager* fbxManager);
	};
}