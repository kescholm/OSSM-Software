#ifndef OSSM_SOFTWARE_FR_H
#define OSSM_SOFTWARE_FR_H

#include "abstract/LanguageStruct.h"

// TODO: Requires validation by a native french speaker.
//  These have been translated by Google Translate.
static const LanguageStruct fr = {
    .DeepThroatTrainerSync = "DeepThroat Sync",
    .Error = "Erreur",
    .Homing = "FR - Homing",
    .HomingSensorless = "FR - Finding Home Sensorless",
    .HomingTookTooLong =
        "Le homing a pris trop de temps.Veuillez vérifier votre câblage et "
        "réessayer.",
    .Idle = "Inactif",
    .NoInternalLoop = "Aucun gestionnaire d'affichage implémenté.",
    .Restart = "Redémarrage",
    .Settings = "Paramètres",
    .SimplePenetration = "Pénétration simple",
    .StateNotImplemented = "État: %u non implémenté.",
    .StrokeEngine = "Stroke Engine",
    .StrokeTooShort =
        "Course trop courte. Veuillez vérifier votre courroie d'entraînement.",
    .YouShouldNotBeHere = "Vous ne devriez pas être ici.",
    .GetHelp = "Obtenir de l'aide",
    .GetHelpLine1 = "Sur Discord,",
    .GetHelpLine2 = "ou GitHub",
    .Skip = "Cliquez pour quitter"};

#endif  // OSSM_SOFTWARE_FR_H
