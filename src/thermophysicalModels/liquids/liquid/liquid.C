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

\*---------------------------------------------------------------------------*/

#include "error.H"

#include "liquid.H"
#include "HashTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(liquid, 0);
    defineRunTimeSelectionTable(liquid,);
    defineRunTimeSelectionTable(liquid, Istream);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::liquid> Foam::liquid::New(Istream& is)
{
    if (debug)
    {
        Info<< "liquid::New(Istream&) : "
            << "constructing liquid"
            << endl;
    }

    word liquidType(is);

    word coeffs(is);

    if (coeffs == "defaultCoeffs")
    {
        ConstructorTable::iterator cstrIter =
            ConstructorTablePtr_->find(liquidType);

        if (cstrIter == ConstructorTablePtr_->end())
        {
            FatalErrorIn("liquid::New(Istream&)")
                << "Unknown liquid type " << liquidType
                << nl << nl
                << "Valid liquid types are:" << nl
                << ConstructorTablePtr_->sortedToc()
                << abort(FatalError);
        }

        return autoPtr<liquid>(cstrIter()());
    }
    else if (coeffs == "coeffs")
    {
        IstreamConstructorTable::iterator cstrIter =
            IstreamConstructorTablePtr_->find(liquidType);

        if (cstrIter == IstreamConstructorTablePtr_->end())
        {
            FatalErrorIn("liquid::New(Istream&)")
                << "Unknown liquid type " << liquidType
                << endl << endl
                << "Valid liquid types are:" << nl
                << IstreamConstructorTablePtr_->sortedToc()
                << abort(FatalError);
        }

        return autoPtr<liquid>(cstrIter()(is));
    }
    else
    {
        FatalErrorIn("liquid::New(Istream&)")
            << "liquid type " << liquidType
            << ", option " << coeffs << " given"
            << ", should be coeffs or defaultCoeffs"
            << abort(FatalError);

        return autoPtr<liquid>(NULL);
    }
}


// ************************************************************************* //
