#pragma once

#include <Engine/MeshEdit/Parameterization/SphericalEmbedding/SphericalEmbedding.h>
#include <Engine/MeshEdit/Preprocessing.h>
#include <UHEMesh/HEMesh.h>
#include <UGM/UGM>
#include <Eigen/Sparse>
#include <Eigen/Dense>

using namespace Eigen;

namespace Ubpa {
	class TriMesh;
	class Preprocessing;
	class Paramaterize;
	enum ViewMode;
	// mesh boundary == 1
	class CdVARAP : public SphericalEmbedding {
	public:
		CdVARAP(Ptr<TriMesh> triMesh) : SphericalEmbedding(triMesh) { }
		CdVARAP(Ptr<Parameterization> embd) : SphericalEmbedding(embd) { }
		CdVARAP(Ptr<Preprocessing> preproc) : SphericalEmbedding(preproc) { }
	public:
		static const Ptr<CdVARAP> New(Ptr<TriMesh> triMesh) {
			return Ubpa::New<CdVARAP>(triMesh);
		}
		static const Ptr<CdVARAP> New(Ptr<Parameterization> embd) {
			return Ubpa::New<CdVARAP>(embd);
		}
		static const Ptr<CdVARAP> New(Ptr<Preprocessing> preproc) {
			return Ubpa::New<CdVARAP>(preproc);
		}
	public:
		bool Run();
		bool Iterate();
		bool IterateTillDone();

	protected:
		void InitRadius();
		void InitTetra();
		void InitParaSolver();
		void UpdateTetra();
		void UpdateParaMap();
		void UpdateRadius();
		double Weight(Matrix3d xt, int i, int j);
		double Weight(Matrix3d xt, int i);
		double Energy();

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
	protected:
		double							energy_;
		double							epsilon = 0.001;
		Matrix3d* tetra_array_;
		SparseLU<SparseMatrix<double>>	para_solver_;
		SparseMatrix<double, RowMajor>	L;
		SparseLU<SparseMatrix<double>> solver;
	};
}

