/****************************************************************************/
/*    Project:     utility                                               	*/
/*    File:        utility.hpp                                              */
/*    Date:        15.9.2022                                                */
/*    Name:        Amit Regev                                               */
/****************************************************************************/

#ifndef __ILRD25__UTILITY__
#define __ILRD25__UTILITY__


#if __cplusplus<201103
#define NULL_PTR NULL
#define NO_EXCEPT throw()
#else
#define NULL_PTR nullptr
#define NO_EXCEPT noexcept

#endif // #if __cplusplus<201103


#endif // #ifndef __ILRD25__UTILITY__

