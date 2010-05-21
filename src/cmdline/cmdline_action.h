// cmdline_action.h                                   -*-c++-*-
//
//   Copyright 2004 Daniel Burrows

#ifndef CMDLINE_ACTION_H
#define CMDLINE_ACTION_H

#include "cmdline_common.h"

/** \file cmdline_action.h
 */

class pkgPolicy;

/// \todo The command-line state should probably be encapsulated
/// as an object.

/// \todo allow_auto in cmdline_applyaction() is a hack.  We should
/// use action-groups to suppress auto-installation (not currently
/// done but makes sense) and tidy up afterwards?

/** \brief Apply the given command-line action to the given package,
 *  updating the command-line state appropriately.
 *
 *  \param action The action to apply to the package.
 *
 *  \param pkg The package whose state is to be modified.
 *
 *  \param seen_virtual_packages The set of pure virtual packages that
 *         have already been "seen".  If pkg is a pure virtual package
 *         in this set, it will not be ignored even if a provider is
 *         already installed or going to be installed.  If only one
 *         package provides pkg, that package will be targeted by the
 *         action; otherwise cmdline_applyaction will fail but not
 *         print the usual error message.  The purpose of this option
 *         is to improve the error messages that are printed on the
 *         second pass, but more importantly to ensure that the
 *         dependencies of virtual packages are installed. (bug #475006)
 *
 *  \param to_install The set of packages that are currently marked
 *  to-be-installed; will be updated in accordance with the selected
 *  action.
 *
 *  \param to_hold The set of packages that are currently marked
 *  to-be-held; will be updated in accordance with the selected
 *  action.
 *
 *  \param to_remove The set of packages that are currently marked
 *  to-be-removed; will be updated in accordance with the selected
 *  action.
 *
 *  \param to_purge The set of packages that are currently marked
 *  to-be-purged; will be updated in accordance with the selected
 *  action.
 *
 *  \param verbose The verbosity level at which this command should
 *  operate.
 *
 *  \param source The version-source to be used for this package.
 *
 *  \param sourcestr The string associated with the version source, or
 *  "" if there is no associated string.
 *
 *  \param policy A current policy object (passed as a parameter to
 *  avoid creating a separate one for each action).
 *
 *  \param arch_only If \b true, when packages' build-depends are
 *  satisfied, only architecture-dependent build depends are used;
 *  Build-Depends-Indep and Build-Conflicts-Indep lines are ignored.
 *
 *  \param allow_auto If \b false, auto-installation of dependencies
 *  will be disabled regardless of the value of Auto-Install.
 */
bool cmdline_applyaction(cmdline_pkgaction_type action,
			 pkgCache::PkgIterator pkg,
			 std::set<pkgCache::PkgIterator> &seen_virtual_packages,
			 pkgset &to_install, pkgset &to_hold,
			 pkgset &to_remove, pkgset &to_purge,
			 int verbose,
			 cmdline_version_source source,
			 const string &sourcestr,
			 pkgPolicy &policy,
			 bool arch_only,
			 bool allow_auto);

/** \brief Apply the given command-line action to the given package,
 *  updating the command-line state appropriately.
 *
 *  \param s The name of the package or the match pattern selecting the
 *           packages whose state is to be modified.
 *
 *  \param action The action to apply to the package.
 *
 *  \param pkg The package whose state is to be modified.
 *
 *  \param seen_virtual_packages The set of pure virtual packages that
 *         have already been "seen".  If a pure virtual package in
 *         this set is encountered, it will not be ignored even if a
 *         provider is already installed or going to be installed.  If
 *         only one package provides it, that package will be targeted
 *         by the action; otherwise cmdline_applyaction will fail but
 *         not print the usual error message.  The purpose of this
 *         option is to improve the error messages that are printed on
 *         the second pass, but more importantly to ensure that the
 *         dependencies of virtual packages are installed. (bug
 *         #475006)
 *
 *  \param to_install The set of packages that are currently marked
 *  to-be-installed; will be updated in accordance with the selected
 *  action.
 *
 *  \param to_hold The set of packages that are currently marked
 *  to-be-held; will be updated in accordance with the selected
 *  action.
 *
 *  \param to_remove The set of packages that are currently marked
 *  to-be-removed; will be updated in accordance with the selected
 *  action.
 *
 *  \param to_purge The set of packages that are currently marked
 *  to-be-purged; will be updated in accordance with the selected
 *  action.
 *
 *  \param verbose The verbosity level at which this command should
 *  operate.
 *
 *  \param policy A current policy object (passed as a parameter to
 *  avoid creating a separate one for each action).
 *
 *  \param arch_only If \b true, when packages' build-depends are
 *  satisfied, only architecture-dependent build depends are used;
 *  Build-Depends-Indep and Build-Conflicts-Indep lines are ignored.
 *
 *  \param allow_auto If \b false, auto-installation of dependencies
 *  will be disabled regardless of the value of Auto-Install.
 */
bool cmdline_applyaction(string s,
			 std::set<pkgCache::PkgIterator> &seen_virtual_packages,
			 cmdline_pkgaction_type action,
			 pkgset &to_install, pkgset &to_hold,
			 pkgset &to_remove, pkgset &to_purge,
			 int verbose,
			 pkgPolicy &policy, bool arch_only,
			 bool allow_auto);

/** \brief Parses a list of actions and executes them.
 *
 *  If there is a syntax or other error, all the commands up to the
 *  point of the error will be executed regardless.
 *
 *  \param s The string to be parsed.
 *
 *  \param seen_virtual_packages The set of pure virtual packages that
 *         have already been "seen".  If a pure virtual package in
 *         this set is encountered, it will not be ignored even if a
 *         provider is already installed or going to be installed.  If
 *         only one package provides it, that package will be targeted
 *         by the action; otherwise cmdline_applyaction will fail but
 *         not print the usual error message.  The purpose of this
 *         option is to improve the error messages that are printed on
 *         the second pass, but more importantly to ensure that the
 *         dependencies of virtual packages are installed. (bug
 *         #475006)
 *
 *  \param to_install The set of packages that are currently marked
 *  to-be-installed; will be updated in accordance with the selected
 *  action.
 *
 *  \param to_hold The set of packages that are currently marked
 *  to-be-held; will be updated in accordance with the selected
 *  action.
 *
 *  \param to_remove The set of packages that are currently marked
 *  to-be-removed; will be updated in accordance with the selected
 *  action.
 *
 *  \param to_purge The set of packages that are currently marked
 *  to-be-purged; will be updated in accordance with the selected
 *  action.
 *
 *  \param verbose The verbosity level at which this command should
 *  operate.
 *
 *  \param policy A current policy object (passed as a parameter to
 *  avoid creating a separate one for each action).
 *
 *  \param arch_only If \b true, when packages' build-depends are
 *  satisfied, only architecture-dependent build depends are used;
 *  Build-Depends-Indep and Build-Conflicts-Indep lines are ignored.
 *
 *  \param allow_auto If \b false, auto-installation of dependencies
 *  will be disabled regardless of the value of Auto-Install.
 */
void cmdline_parse_action(string s,
			  std::set<pkgCache::PkgIterator> &seen_virtual_packages,
			  pkgset &to_install, pkgset &to_hold,
			  pkgset &to_remove, pkgset &to_purge,
			  int verbose,
			  pkgPolicy &policy, bool arch_only,
			  bool allow_auto);

#endif // CMDLINE_ACTION_H