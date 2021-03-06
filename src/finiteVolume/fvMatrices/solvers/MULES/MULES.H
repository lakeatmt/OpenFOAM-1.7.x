/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2010 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Global
    MULES

Description
    MULES: Multidimensional universal limiter with explicit solution.

    Solve a convective-only transport equation using an explicit universal
    multi-dimensional limiter.

    Parameters are the variable to solve, the normal convective flux and the
    actual explicit flux of the variable which is also used to return limited
    flux used in the bounded-solution.

SourceFiles
    MULES.C

\*---------------------------------------------------------------------------*/

#ifndef MULES_H
#define MULES_H

#include "volFields.H"
#include "surfaceFieldsFwd.H"
#include "primitiveFieldsFwd.H"
#include "zeroField.H"
#include "geometricOneField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace MULES
{

template<class RhoType, class SpType, class SuType>
void explicitSolve
(
    const RhoType& rho,
    volScalarField& psi,
    const surfaceScalarField& phiBD,
    surfaceScalarField& phiPsi,
    const SpType& Sp,
    const SuType& Su,
    const scalar psiMax,
    const scalar psiMin
);

void explicitSolve
(
    volScalarField& psi,
    const surfaceScalarField& phiBD,
    surfaceScalarField& phiPsi,
    const scalar psiMax,
    const scalar psiMin
);

template<class RhoType, class SpType, class SuType>
void implicitSolve
(
    const RhoType& rho,
    volScalarField& gamma,
    const surfaceScalarField& phi,
    surfaceScalarField& phiCorr,
    const SpType& Sp,
    const SuType& Su,
    const scalar psiMax,
    const scalar psiMin
);

void implicitSolve
(
    volScalarField& gamma,
    const surfaceScalarField& phi,
    surfaceScalarField& phiCorr,
    const scalar psiMax,
    const scalar psiMin
);

template<class RhoType, class SpType, class SuType>
void limiter
(
    scalarField& allLambda,
    const RhoType& rho,
    const volScalarField& psi,
    const surfaceScalarField& phiBD,
    const surfaceScalarField& phiCorr,
    const SpType& Sp,
    const SuType& Su,
    const scalar psiMax,
    const scalar psiMin,
    const label nLimiterIter
);

} // End namespace MULES

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "MULESTemplates.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
