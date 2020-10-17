#include "dispatcher_utility.hpp"
#include "observer/main/agent.hpp"
#include "observer/main/daemon.hpp"

int main(int argc, const char* argv[]) {
  //
  // Initialize
  //

  auto scoped_dispatcher_manager = krbn::dispatcher_utility::initialize_dispatchers();

  signal(SIGUSR1, SIG_IGN);
  signal(SIGUSR2, SIG_IGN);

  //
  // Check euid
  // (observer is launched from LaunchDaemons (root) and LaunchAgents (user).)
  //

  bool root = (geteuid() == 0);

  if (root) {
    return krbn::observer::main::daemon();
  } else {
    return krbn::observer::main::agent();
  }
}
