# Contributing to ds_lib

Thank you for your interest in contributing! This document explains how to get started.

---

## How to Contribute

### 1. Fork the repository
Click the **Fork** button on the top right of the repo page.

### 2. Clone your fork
```bash
git clone https://github.com/YOUR_USERNAME/ds_lib.git
cd ds_lib
```

### 3. Create a new branch
```bash
git checkout -b feat/your-feature-name
```

### 4. Make your changes
- Follow the existing code style
- Add tests for any new functionality
- Make sure all existing tests still pass with `make test`
- Check for memory leaks with `make valgrind`

### 5. Commit your changes
```bash
git add .
git commit -m "feat: add your feature description"
```

Use these commit prefixes:
- `feat:` — new feature
- `fix:` — bug fix
- `docs:` — documentation change
- `test:` — adding or fixing tests
- `refactor:` — code cleanup

### 6. Push and open a Pull Request
```bash
git push origin feat/your-feature-name
```
Then go to GitHub and click **New Pull Request**.

---

## What You Can Contribute

- New data structures (e.g. Min Heap, Trie, Graph)
- More test cases
- Performance improvements
- Documentation improvements
- Bug fixes

---

## Code Style Rules

- Use 4 spaces for indentation
- Keep functions small and focused
- Every function must handle NULL input gracefully
- Add a comment above any non-obvious logic
- Header files must have include guards (`#ifndef`)

---

## Running Tests Before Submitting

Always run tests before opening a pull request:

```bash
make test
```

All 81 tests must pass. If you added new features, add tests for them too.

---

## Questions?

Open an **Issue** on GitHub and ask — happy to help!
