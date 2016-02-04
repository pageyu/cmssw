#ifndef DTSegment_DTSegmentUpdator_h
#define DTSegment_DTSegmentUpdator_h

/** \class DTSegmentUpdator
 *
 * Perform linear fit and hits update for DT segments.
 * Update a segment by improving the hits thanks to the refined knowledge of
 * impact angle and position (also along the wire) and perform linear fit on
 * improved hits.
 *
 * $Date: 2010/04/16 14:11:06 $
 * $Revision: 1.18 $
 * \author Stefano Lacaprara - INFN Legnaro <stefano.lacaprara@pd.infn.it>
 * \author Riccardo Bellan - INFN TO <riccardo.bellan@cern.ch>
 *
 */

/* C++ Headers */
#include <vector>

#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "Geometry/DTGeometry/interface/DTGeometry.h"

/* ====================================================================== */

/* Collaborating Class Declarations */
class DTSegmentCand;
class DTRecSegment2D;
class DTRecSegment4D;
class DTLinearFit;
class DTRecHitBaseAlgo;

namespace edm{class EventSetup; class ParameterSet;}

/* Class DTSegmentUpdator Interface */
class DTSegmentUpdator{

  public:

    /// Constructor
    DTSegmentUpdator(const edm::ParameterSet& config) ;

    /// Destructor
    ~DTSegmentUpdator() ;

    /* Operations */ 

    /** do the linear fit on the hits of the segment candidate and update it.
     * Returns false if the segment candidate is not good() */
    bool fit(DTSegmentCand* seg) const;

    /** ditto for true segment: since the fit is applied on a true segment, by
     * definition the segment is "good", while it's not the case for just
     * candidates */
    void fit(DTRecSegment2D* seg) const;

    /** ditto for true segment 4D, the fit is done on either projection and then
     * the 4D direction and position is built. Since the fit is applied on a
     * true segment, by definition the segment is "good", while it's not the
     * case for just candidates */
    void fit(DTRecSegment4D* seg) const;

    /// recompute hits position and refit the segment4D
    void update(DTRecSegment4D* seg, const bool calcT0 = false) const;

    /// recompute hits position and refit the segment2D
    void update(DTRecSegment2D* seg) const;

    void calculateT0corr(DTRecSegment2D* seg) const;
    void calculateT0corr(DTRecSegment4D* seg) const;

    /// set the setup
    void setES(const edm::EventSetup& setup);

  protected:

  private:
    DTLinearFit* theFitter; // the linear fitter
    DTRecHitBaseAlgo* theAlgo; // the algo for hit reconstruction
    edm::ESHandle<DTGeometry> theGeom; // the geometry

    void updateHits(DTRecSegment2D* seg,
                    GlobalPoint &gpos,
                    GlobalVector &gdir,
                    const int step=2) const;

    /// interface to LinearFit
    void fit(const std::vector<float>& x,
             const std::vector<float>& y, 
             const std::vector<float>& sigy,
             LocalPoint& pos,
             LocalVector& dir,
             AlgebraicSymMatrix& covMat,
             double& chi2) const;

    void Fit4Var(const std::vector<float>& xfit,
                 const std::vector<float>& yfit,
                 const std::vector<int>& lfit,
                 const std::vector<double>& tfit,
                 const int nptfit,
                 float& cminf, double& vminf,
                 double& chi2fit) const;

    bool vdrift_4parfit;
    double T0_hit_resolution;
    bool debug;

};

#endif // DTSegment_DTSegmentUpdator_h
