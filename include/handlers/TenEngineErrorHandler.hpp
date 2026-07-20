

#ifndef TENTRILLIONGAMEENGINE_ENGINEERRORHANDLER_HPP
#define TENTRILLIONGAMEENGINE_ENGINEERRORHANDLER_HPP
namespace TenTrillion {
/**
 * This creates the global error handler, that catches errors and displays the
 * messageBox accordingly.
 */
void SetEngineErrorHandler();
/**
 * This allows the engine to be immediately terminated.
 * @param msg Termination message.
 */
void TerminateEngineProcess(const char *msg);
} // namespace TenTrillion

#endif // TENTRILLIONGAMEENGINE_ENGINEERRORHANDLER_HPP
