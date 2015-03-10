#ifndef VertexRestorer_h
#define VertexRestorer_h 1

#include "marlin/Processor.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include "lcio.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#include "MathOperator.hh"
#include "TrackOperator.hh"
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/ReconstructedParticleImpl.h>
#include <IMPL/VertexImpl.h>
#include <EVENT/MCParticle.h>
#include <UTIL/LCRelationNavigator.h>
#include <EVENT/LCCollection.h>
#include <EVENT/Vertex.h>
#include <EVENT/Track.h>
#include <EVENT/ParticleID.h>
#include <IMPL/ParticleIDImpl.h>
using namespace lcio ;
using namespace marlin ;


/** 
 *  <h4> ==== VertexRestorer Processor ==== </h4>
 *  
 * Used to bla bla
 * 
 * @param ROOTFileName: Name of the output ROOT file
 *   
 * @author Bilokin Sviatoslav, LAL
 * @version $Id: VertexRestorer.h,v 1.0 2010/02/18 Exp $ 
 */

namespace TTbarAnalysis
{
	class VertexRestorer : public Processor {
	  
	 public:
	  
	  virtual Processor*  newProcessor() { return new VertexRestorer ; }
	  
	  
	  VertexRestorer() ;
	  
	  virtual void init() ;
	  virtual void processRunHeader( LCRunHeader* run ) ;
	  virtual void processEvent( LCEvent * evt ) ; 
	  virtual void check( LCEvent * evt ) ; 
	  virtual void end() ;
	  
	  void PrintTrack(EVENT::Track * track); 
	  void PrintParticle(EVENT::ReconstructedParticle * particle);

	  std::vector< EVENT::ReconstructedParticle * > * RefineVertices(EVENT::LCCollection * main, EVENT::LCCollection * sec);
	  std::vector< EVENT::ReconstructedParticle * > AddParticles(const std::vector< EVENT::ReconstructedParticle * > & pri, EVENT::Vertex * sec, const std::vector< EVENT::ReconstructedParticle * > * toCompare = NULL);


	  bool CompareParticles(const EVENT::ReconstructedParticle * particle1, const EVENT::ReconstructedParticle * particle2, bool verbose = false); 
	  bool CompareParticles(const EVENT::MCParticle * particle1, const EVENT::ReconstructedParticle * particle2); 
	  void CompareCollections(std::vector< EVENT::ReconstructedParticle * > * detected, EVENT::LCCollection * missed, EVENT::LCCollection * bstar);
	  std::vector< EVENT::ReconstructedParticle * > * RestoreVerticesPFO(EVENT::LCCollection * main, EVENT::LCCollection * sec); 
	  std::vector< EVENT::ReconstructedParticle * > * RestoreVertices(EVENT::Vertex * primary, EVENT::LCCollection * sec); 
	  std::vector< EVENT::ReconstructedParticle * > * RestoreVertices(EVENT::LCCollection * sec, EVENT::LCCollection * rel); 
	  std::vector< EVENT::ReconstructedParticle * > GetAdditionalParticles(const std::vector< EVENT::ReconstructedParticle * > & pri, EVENT::Vertex * sec, const std::vector< EVENT::ReconstructedParticle * > * toCompare = NULL);
	  float GetDeviation(const EVENT::ReconstructedParticle * particle, double * pos);
	  float GetError(const EVENT::ReconstructedParticle * particle);
	  EVENT::ReconstructedParticle * CopyParticle(const EVENT::ReconstructedParticle * particle, const EVENT::Vertex * vertex, float theta = 0.0);
	  bool IsDublicate(const EVENT::ReconstructedParticle * particle, std::vector< EVENT::ReconstructedParticle * > & data);
	  void WritePrimaries(TrackOperator & opera, EVENT::LCCollection * pricol);
	  void AddParticleID(EVENT::ReconstructedParticle * particle, float theta);
	  void ClearVariables();
	  void AnalyseSecondaries(EVENT::LCCollection * main, EVENT::LCCollection * missed);
	 protected:

	  std::string _colName ;
	  std::string _colPriName ;
	  std::string _colSecName ;
	  std::string _colJetName ;
	  std::string _colJetRelName ;
	  std::string _clusterName ;
	  std::string _colMissedName ;
	  std::string _colBStarName ;
	 
	  static const int MAXN = 30;
	  float _fakeMomentum[MAXN];
	  float _bstarMomentum[MAXN];
	  float _missedMomentum[MAXN];
	  
	  float _fakeDeviation[MAXN];
	  float _bstarDeviation[MAXN];
	  float _missedDeviation[MAXN];
	  float _fakeError[MAXN];
	  float _bstarError[MAXN];
	  float _missedError[MAXN];

	  float _missedAngle[MAXN];
	  float _fakeAngle[MAXN];
	  static const int MAXP = 100;
	  int _primariesTotal;
	  float _primeOffset[MAXP];
	  float _primeDeviation[MAXP];
	  float _primeMomentum[MAXP];
	  float _primeError[MAXP];
		
	  double ip[3];
	  float _aParameter;
	  float _bParameter;
	  
	  int _missedDetected;
	  int _bstarDetected;
	  int _fakeDetected;

	  int _missedTotal;
	  int _bstarTotal;
	  int _detectedTotal;
	  int _missedRecoTotal;
	  float _missedRecoMomentum[MAXN];
	  float _missedRecoTheta[MAXN];
	  float _missedRecoDeviation[MAXN];
	  int _nRun ;
	  int _nEvt ;


	  float _offsetCut;
	  float _angleCut;

	  TFile* hfile ;
	  std::string _hfilename ;
	  TTree* _Tree;
	  TTree* _primaryTree;
	  TrackOperator myTrackOperator;
	  EVENT::Vertex * myPrimary;

	} ;
}
	#endif



