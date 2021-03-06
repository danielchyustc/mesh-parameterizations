#pragma once

#include <Engine/MeshEdit/Parameterization/SphericalEmbedding/SphericalEmbedding.h>
#include <Engine/MeshEdit/Preprocessing.h>
#include <UHEMesh/HEMesh.h>
#include <UGM/UGM>
#include <Eigen/Sparse>

using namespace Eigen;

namespace Ubpa {
	class TriMesh;
	class Preprocessing;
	enum ViewMode;

	// mesh boundary == 0
	// spherical barrycentric embedding
	class SBE : public SphericalEmbedding {
	public:
		SBE(Ptr<TriMesh> triMesh) : SphericalEmbedding(triMesh) { }
		SBE(Ptr<Parameterization> embd) : SphericalEmbedding(triMesh) { }
		SBE(Ptr<Preprocessing> preproc) : SphericalEmbedding(preproc) { }
	public:
		static const Ptr<SBE> New(Ptr<TriMesh> triMesh) {
			return Ubpa::New<SBE>(triMesh);
		}
		static const Ptr<SBE> New(Ptr<Parameterization> embd) {
			return Ubpa::New<SBE>(embd);
		}
		static const Ptr<SBE> New(Ptr<Preprocessing> preproc) {
			return Ubpa::New<SBE>(preproc);
		}
	public:
		bool Run();
		bool Iterate();
		bool IterateTillDone();

	private:
		void UpdateParaMap();
		double LaplaceAt(RowVectorXd f, int i);
		VectorXd LaplaceAt(MatrixXd f, int i);
		MatrixXd Laplace(MatrixXd f);
		double Energy(RowVectorXd f);
		double Energy(MatrixXd f);

	private:
		class V;
		class E;
		class P;
		class V : public TVertex<V, E, P> {
		public:
			vecf3 pos;
		};
		class E : public TEdge<V, E, P> { };
		class P : public TPolygon<V, E, P> { };
	private:
		double					energy_;
		double					delta_t = 0.1;
		double					epsilon = 0.001;
	};
}