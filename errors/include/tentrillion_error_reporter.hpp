#ifndef TENTRILLIONGAMEENGINE_ERRORREPORTER_HPP
#define TENTRILLIONGAMEENGINE_ERRORREPORTER_HPP

#include <cstddef>
enum class tentrillion_error_reporter_buttons { Ok, SendBugReport };

/**
 * @brief When the error reporter is not launched from the parent TenTrillion
 * session.
 *
 */
constexpr const char *not_launched_from_parent_default =
	"Not launched from TenTrillion Parent!";
/**
 * @brief The OK button.
 *
 */
constexpr const char *ok_button = "Ok";
/**
 * @brief The Send Bug Report Button.
 *
 */
constexpr const char *send_bug_report_button = "Send Bug Report";
/**
 * @brief The EMAIL address for the
 *
 */
constexpr const char *recipient_email_address = "tentrillion@thefirey33.net";

#endif