/*
 * @brief Функции генерации случайных чисел на стороне сервера
 * random_config.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#if defined( WIN32 )
    #if defined( FLOADER_DLL )
        #define RANDOM_EXPORT __declspec(dllexport)
    #else
        #define RANDOM_EXPORT __declspec(dllimport)
    #endif

    #ifndef DLLIMPORT
        #define DLLIMPORT __declspec(dllexport)
    #endif

#else
    #define RANDOM_EXPORT
#endif /* FLOADER_DLL */


