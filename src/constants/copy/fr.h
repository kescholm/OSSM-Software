//
// Created by Andrew Koenig on 2023-10-15.
//

#ifndef OSSM_SOFTWARE_FR_H
#define OSSM_SOFTWARE_FR_H

#include "abstract/CopyStruct.h"

// TODO: Requires validation by a native french speaker.
//  These have been translated by Google Translate.
static const CopyStruct fr = {
    .Error = "Erreur",
    .Homing = "FR - Homing",
    .HomingSensorless = "FR - Finding Home Sensorless",
    .HomingTookTooLong =
        "Le homing a pris trop de temps.Veuillez vérifier votre câblage et "
        "réessayer.",
    .NoInternalLoop = "Aucun gestionnaire d'affichage implémenté.",
    .StateNotImplemented = "État: %u non implémenté.",
    .YouShouldNotBeHere = "Vous ne devriez pas être ici.",
};

#endif  // OSSM_SOFTWARE_FR_H
