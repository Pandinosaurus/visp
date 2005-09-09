/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet Lagadic, 2005
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      debug.hh
 * Project:   ViSP
 * Author:    Nicolas Mansard
 *
 * Version control
 * ===============
 *
 *  $Id: vpDebug.h,v 1.5 2005-09-09 07:32:38 crenaudi Exp $
 *
 * Description
 * ============
 *
 * Macro de trace et de debugage
 *
 *   - TRACAGE:    TRACE et ERROR_TRACE fonctionnent comme des printf 
 * avec retour chariot en fin de fonction.
 *                 CERROR et CTRACE fonctionnent comme les flux de sortie 
 * C++ cout et cerr.
 *   - DEBUGAGE:   DEBUG_TRACE(niv,  et DERROR_TRACE(niv, fonctionnent 
 * comme des printf, n'imprimant que si le niveau de trace 'niv' est 
 * superieur au mode de debugage DEBUG_MODE.
 *                 CDEBUG(niv) fonctionne comme le flux de sortie C++ cout.
 *                 DEBUG_ENABLE(niv) vaut 1 ssi le niveau de tracage 'niv'
 * est superieur au  mode de debugage DEBUG_MODE. Il vaut 0 sinon.
 *   - PROG DEFENSIVE: DEFENSIF(a) vaut a ssi le mode defensif est active,
 * et vaut 0 sinon.
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef __VP_DEBUG_HH
#define __VP_DEBUG_HH

#define __VP_TEMPLATE_DEBUG_HH

#include <stdio.h>
#include <iostream>
using namespace std;

#ifndef WIN32
////////////////////////////////////////////////////////////////////////////
// Unix system
//

/* -------------------------------------------------------------------------- */
/* --- TRACE ---------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

#ifndef SILENT_TRACES
#define ERROR_TRACE(a...)   do {\
    std::cerr << "!!\t" << __FILE__ << ": " <<__FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    fprintf (stderr, a); \
    fprintf (stderr, "\n"); \
    fflush (stderr); } while (0) 
#define CERROR std::cerr << "!!\t" << __FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" 
#define TRACE(a...)    do {\
    std::cout << "(N0)" << __FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    printf (a); \
    printf ("\n"); \
    fflush (stdout); } while (0) 
#define CTRACE std::cout << "(N0)" << __FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" 
#endif /* #ifndef SILENT_TRACES */

/* -------------------------------------------------------------------------- */
/* --- DEBUG ---------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

#ifdef DEBUG
#define DERROR_TRACE(niv, a...)  do {\
    if (DEBUG_MODE >= niv) {\
    std::cerr << "(N" << niv << ") " ; \
    std::cerr << __FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    fprintf (stderr, a); \
    fprintf (stderr, "\n"); \
    fflush (stderr); } \
    } while (0)
#define DEBUG_TRACE(niv, a...)   do {\
    if (DEBUG_MODE >= niv) {\
    std::cout << "(N" << niv << ") " ; \
    std::cout <<__FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    printf (a); printf ("\n"); \
    fflush (stdout); } \
    } while (0)
#define CDEBUG(niv) if (DEBUG_MODE < niv) ; else \
    std::cout << "(N" << niv << ") "<< __FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :"  
#define DEBUG_ENABLE(niv) (DEBUG_MODE >= niv)

#else /*#ifdef DEBUG*/
#define DERROR_TRACE(niv, a...)  do {} while (0) 
#define DEBUG_TRACE(niv, a...)   do {} while (0) 
#define CDEBUG(niv) if (1) ; else std::cout  
#define DEBUG_ENABLE(niv) (0)
#endif /*#ifdef DEBUG*/


/* -------------------------------------------------------------------------- */
/* --- DEFENSIF ------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

#ifdef DEFENSIF
#define DEFENSIF(a)  (a)
#else
#define DEFENSIF(a)  (0)
#endif  /*#ifdef DEFENSIF*/


/* -------------------------------------------------------------------------- */
/* --- TRACE ENTREE/SORTIE FONCTION ----------------------------------------- */
/* -------------------------------------------------------------------------- */

#define vpIN_FCT(niv, a...)   do {\
    if (DEBUG_MODE >= niv) {\
    cout <<"begin" << __FILE__ << ": " << __FUNCTION__ <<  "(#" << __LINE__ << ") :"; \
    printf (a); printf ("\n"); \
    fflush (stdout); } \
    } while (0)
 

#define vpOUT_FCT(niv, a...)   do {\
    if (DEBUG_MODE >= niv) {\
    cout <<"begin" << __FILE__ << ": " << __FUNCTION__ <<  "(#" << __LINE__ << ") :"; \
    printf (a); printf ("\n"); \
    fflush (stdout); } \
    } while (0)



/* Macro de trace et de debugage pour les template
 * Ce fichier differe du fichier debug.hh classique par l'absence d'utilisation
 * des macros DEBUG et DEBUG_MODE. Les traces sont definies tout le temps, 
 * et ne depende pas d'une macro definie a la compilation, mais des macros 
 * TEMPLATE_DEBUG et TEMPLATE_DEBUG_MODE definies en debut de fichier .t.cc 
 * (par default, elle vaut 0 : pas de trace). Les lignes de traces sont retires de
 * l'executatble si une directive d'optimisation de compilation (-o3 par
 * exemple) est utilisee (dans ce cas, les branchements conditionnels sont
 * resolu avant la generation du code quand c'est possible, en particulier
 * dans ce cas).
 * L'utilisation classique est :
 * #define TEMPLATE_DEBUG    
 * #define TEMPLATE_DEBUG_MODE      5 
 * #include "template_debug.hh"
 */

#undef TDERROR_TRACE
#undef TDEBUG_TRACE
#undef CTDEBUG
#undef TDEBUG_ENABLE

#ifdef TEMPLATE_DEBUG

#ifndef TEMPLATE_DEBUG_MODE
#define TEMPLATE_DEBUG_MODE 0
#endif /*#ifndef TEMPLATE_DEBUG_MODE*/

#define TDERROR_TRACE(niv, a...)  do {\
    if (TEMPLATE_DEBUG_MODE >= niv) {\
    std::cerr <<__FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    printf (a); \
    fprintf (stderr, "\n"); \
    fflush (stderr); } \
    } while (0)
#define TDEBUG_TRACE(niv, a...)   do {\
    if (TEMPLATE_DEBUG_MODE >= niv) {\
    std::cout << "(N" << niv << ") " ; \
    std::cout <<__FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    printf (a); printf ("\n"); \
    fflush (stdout); } \
    } while (0)
#define CTDEBUG(niv) if (TEMPLATE_DEBUG_MODE < niv) ; else \
    std::cout << "(N" << niv << ") " ; \
    std::cout << __FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :"  
#define TDEBUG_ENABLE(niv) (TDEBUG_MODE >= niv)

#else /*#ifdef TEMPLATE_DEBUG*/
#define TDERROR_TRACE(niv, a...)  do {} while (0) 
#define TDEBUG_TRACE(niv, a...)   do {} while (0) 
#define CTDEBUG(niv) if (1) ; else std::cout  
#define TDEBUG_ENABLE(niv) (0)
#endif /*#ifdef TEMPLATE_DEBUG*/



#else  /* #ifndef WIN32 */
////////////////////////////////////////////////////////////////////////////
// Windows system
//

#ifndef __FUNCTION__
#define __FUNCTION__ " "
#endif

#define vpIN_FCT(niv, a, b)   do {\
    if (DEBUG_MODE >= niv) {\
    cout <<"begin" << __FILE__ << ": " << __FUNCTION__ <<  "(#" << __LINE__ << ") :"; \
    printf (a); printf ("\n"); \
    fflush (stdout); } \
    } while (0)


#define vpOUT_FCT(niv, a, b)   do {\
    if (DEBUG_MODE >= niv) {\
    cout <<"begin" << __FILE__ << ": " << __FUNCTION__ <<  "(#" << __LINE__ << ") :"; \
    printf (a); printf ("\n"); \
    fflush (stdout); } \
    } while (0)



inline void ERROR_TRACE(char *a) {  do {\
    cerr << "!!\t" << __FILE__ << ": " <<__FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    fprintf (stderr, a); \
    fprintf (stderr, "\n"); \
    fflush (stderr); } while (0); };
inline void ERROR_TRACE(char *a, int b) {  do {\
    cerr << "!!\t" << __FILE__ << ": " <<__FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    fprintf (stderr, a, b); \
    fprintf (stderr, "\n"); \
    fflush (stderr); } while (0); };
inline void ERROR_TRACE(char *a, double b) {  do {\
    cerr << "!!\t" << __FILE__ << ": " <<__FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    fprintf (stderr, a, b); \
    fprintf (stderr, "\n"); \
    fflush (stderr); } while (0); };
inline void ERROR_TRACE(char *a, const char *b) {  do {\
    cerr << "!!\t" << __FILE__ << ": " <<__FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    fprintf (stderr, a, b); \
    fprintf (stderr, "\n"); \
    fflush (stderr); } while (0); };
inline void ERROR_TRACE(char *a, unsigned b, const char *c) {  do {\
    cerr << "!!\t" << __FILE__ << ": " <<__FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    fprintf (stderr, a, b, c); \
    fprintf (stderr, "\n"); \
    fflush (stderr); } while (0); };
inline void ERROR_TRACE(char *a, double b, double c) {  do {\
    cerr << "!!\t" << __FILE__ << ": " <<__FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    fprintf (stderr, a, b, c); \
    fprintf (stderr, "\n"); \
    fflush (stderr); } while (0); };
#define CERROR cerr << "!!\t" << __FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :"
inline void TRACE(char *a) {   do {\
    cout <<__FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    printf (a); \
    printf ("\n"); \
    fflush (stdout); } while (0); };
inline void TRACE(char *a, int b) {   do {\
    cout <<__FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    printf (a, b); \
    printf ("\n"); \
    fflush (stdout); } while (0); };
inline void TRACE(char *a, double b, double c) {   do {\
    cout <<__FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    printf (a, b, c); \
    printf ("\n"); \
    fflush (stdout); } while (0); };
inline void TRACE(char *a, double b, double c, double d) {   do {\
    cout <<__FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    printf (a, b, c, d); \
    printf ("\n"); \
    fflush (stdout); } while (0); };
#define CTRACE cout << __FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :"

#ifdef DEBUG
#define DERROR_TRACE(niv, a, b)  do {\
    if (DEBUG_MODE >= niv) {\
    cerr <<__FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    printf (a); \
    fprintf (stderr, "\n"); \
    fflush (stderr); } \
    } while (0)
#define DEBUG_TRACE(niv, a)   do {\
    if (DEBUG_MODE >= niv) {\
    cout <<__FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :" ; \
    printf (a); printf ("\n"); \
    fflush (stdout); } \
    } while (0)
#define CDEBUG(niv) if (DEBUG_MODE < niv) ; else \
    cout << __FILE__ << ": " << __FUNCTION__ << "(#" << __LINE__ << ") :"

#else
#define DERROR_TRACE(niv, a, b)  do {} while (0)
inline void DEBUG_TRACE(int niv, char *a) {  do {} while (0); };
inline void DEBUG_TRACE(int niv, char *a, char *b) { do {} while (0); };
inline void DEBUG_TRACE(int niv, char *a, unsigned char *b) { do {} while (0); };
inline void DEBUG_TRACE(int niv, char *a, unsigned char **b) { do {} while (0); };
inline void DEBUG_TRACE(int niv, char *a, int b, int c) { do {} while (0); };
#define CDEBUG(niv) if (1) ; else cout
#endif


#ifdef DEFENSIF
#define DEFENSIF(a)  (a)
#else
#define DEFENSIF(a)  (0)
#endif



#endif /* #ifndef WIN32 */
////////////////////////////////////////////////////////////////////////////



#endif /* #ifdef __DEBUG_HH */ 

/*
 * Local variables:
 * c-basic-offset: 4
 * End:
 */
