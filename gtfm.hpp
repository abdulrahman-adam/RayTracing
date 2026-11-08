// gtfm.hpp

#ifndef GTFM_H
#define GTFM_H

#include "./qbLinAlg/qbMatrix.h"
#include "ray.hpp"

namespace qbRT
{
    //Define flag values.
    constexpr bool FWDTFORM = true;
    constexpr bool DCKTFORM = false;

    class GTform
    {
        public:
            // Constructor and destructor
            GTform();
            ~GTform();

            // Construct from a pair of matrices.
            GTform(const qbMatrix2<double> &fwd, const qtMatrix<double> &bck);
            //Function to set translation, rotation and scale components.
            void SetTransform( const qbVector<double> &translation,
                               const qbVector<double> &rotation,
                               const qbVector<double> &scale);
            // Function to return the transform matrices.
            qbMatrix2<double> GetForward();
            qbMatrix2<double> GetBackward();

            //Function to apply the transform.
            qbRT::Ray Apply(const qbRT::Ray &inputRay, bool dirFlag);
            qbVector<double> Apply(const qbVector<double> &imputVector, bool dirFlag);
            // Overload operators
            friend GTform operator* (const qbRT::GTform &rhs, const qbRT::GTform::GTform &rhs);

            //Overload the assignment operator;
            GTform operator* (const GTform &rhs);

            // Function to print transform matrix of vectors.
            private:
                static void PrintVector(const qbVector<double> &matrix);
            private:
                qbMatrix2<double> m_fwdtfm {4, 4};
                qbMatrix2<double> m_bckfm {4, 4};
    };   
}

#endif