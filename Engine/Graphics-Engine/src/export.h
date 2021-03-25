#ifndef EXPORT_H
#define EXPORT_H

#ifdef ENGINE_EXPORTS
#define GENGINE_API __declspec(dllexport) // Especifica clase para exportacion
#else
#define GENGINE_API __declspec(dllexport) // Especifica clase para importacion
#endif // GENGINE_EXPORT

#endif