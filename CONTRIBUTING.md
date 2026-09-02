# Contributing

### Introduction

Before anything make sure to have read the [README](./README.md) for instructions on building and an introduction to the project, the [TODO](./TODO.md) list and the documentation found at [Documentation](https://avisdylan.github.io/jf-framework/html/).

### Coding style

We use a unified C/C++ code style via [.clang-format](./.clang-format).
- Formatting rules are found in [.clang-format](./.clang-format).
- Most modern IDEs automatically pick up on the format file.
- Run your IDEs auto format or use `clang-format -i` before committing.

 ### Pull request guidelines

- Keep pull requests small to make them easier to review by maintainers.
- Document code properly, try to minimize inline comments and add Doxygen comments with `/** ... */`.
- Test changes made for all supported architectures, instructions are found in [README](./README.md#how-to-build).
- Only refactor code related to your changes.
- Follow subsystem boundaries, don't mix unrelated changes. E.g don't put architecture specific code in generic kernel code `src/kernel/`.
- If your PR completes or changes a TODO item, update [TODO](./TODO.md) accordingly. Put `[x]` if you've completed something, `[-]` if it's still in progress, and `[ ]` if it's not started.
- If your PR effects anything in [README](./README.md) update the readme accordingly.

### Licensing

By submitting code to this repository, you agree that your contribution is licensed under the project's [GPLv3](./License.txt) license. You must ensure all code you submit is your own work or compatible with [GPLv3](./License.txt). Do not submit code copied from sources that use incompatible licenses.

### AI generated code

**AI-generated/assisted code is allowed under the following conditions:**
- All AI code must be manually reviewed by a human.
- The contributor must verify that all code is compatible with [GPLv3](./License.txt) and does not originate from sources incompatible with the license.
- AI code must follow all project rules, including [code style](#coding-style), and [PR guidelines](#pull-request-guidelines).
- Contributors are responsible for ensuring that AI code is original, safe, and correct.

### Before you start

**You must complete these steps before starting:**
- Build the library, instructions are at [README](./README.md#how-to-build).
- Familiarize yourself with the documentation found at [Documentation](https://avisdylan.github.io/jf-framework/html/).
- Familiarize yourself with the TODO list found at [TODO](./TODO.md).
- Read over the codebase.
- Fork the repo.
