

#ifndef TENTRILLIONGAMEENGINE_TENGL_HPP
#define TENTRILLIONGAMEENGINE_TENGL_HPP
#include "TenBaseService.hpp"

#include <TenTrillionGameEngineExport.h>
namespace TenTrillion {
/**
 * TenTrillion OpenGL API.
 * This is the OpenGL API accessor and wrapper for the TenTrillion.
 */
class TENTRILLIONGAMEENGINE_EXPORT TenGL : TenBaseService {
  public:
	~TenGL() override = default;
	explicit TenGL(TenTrillionGameEngine *engineReference)
		: TenBaseService(engineReference) {}

	void InitializeService() override;
	void DeInitializeService() override;
};
} // namespace TenTrillion

#endif // TENTRILLIONGAMEENGINE_TENGL_HPP
