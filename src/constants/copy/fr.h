#ifndef OSSM_SOFTWARE_FR_H
#define OSSM_SOFTWARE_FR_H

#include "abstract/LanguageStruct.h"

// TODO: Requires validation by a native french speaker.
//  These have been translated by Google Translate.
static const LanguageStruct fr = {
    .Error = "Erreur",
    .Homing = "FR - Homing",
    .HomingSensorless = "FR - Finding Home Sensorless",
    .HomingTookTooLong =
        "Le homing a pris trop de temps.Veuillez vérifier votre câblage et "
        "réessayer.",
    .NoInternalLoop = "Aucun gestionnaire d'affichage implémenté.",
    .StateNotImplemented = "État: %u non implémenté.",
    .YouShouldNotBeHere = "Vous ne devriez pas être ici.",
    .Idle = "Inactif",
    .StrokeTooShort =
        "Course trop courte. Veuillez vérifier votre courroie "
        "d'entraînement."};

#endif  // OSSM_SOFTWARE_FR_H
