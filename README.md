# OSSM-Software
This is the public software in use on the OSSM

Certainly! Here's a more detailed "Contributing" section for your `README.md`:

---

## Contributing

Firstly, thank you for considering contributing to our open-source library! Community contributions help make our library more robust and beneficial for everyone. This section will guide you through our contribution process.

### Setting Up Your Development Environment

Follow the instructions in the [Setting Up `pre-commit` for Development](#setting-up-pre-commit-for-development) section above to ensure that your code meets our standards before you submit it.

### Contribution Guidelines

1. **Fork & Clone**:

   Begin by forking this repository, then clone your fork locally:

   ```bash
   git clone https://github.com/<your-username>/<repository-name>.git
   ```

   Replace `<your-username>` with your GitHub username and `<repository-name>` with the name of this repository.

2. **Branching**:

   Always create a new branch for your changes to ensure that the main branch remains stable. This makes the review process more straightforward:

   ```bash
   git checkout -b <branch-name>
   ```

   Replace `<branch-name>` with a descriptive name for your branch  (e.g., `feature/OSSM-4-new-feature-name` or `bugfix/OSSM-12-bug-description`).
   
    Please include your ticket number from the [OSSM-Software Project Board](https://track.researchanddesire.com) so that your commit messages and PR status tracked and shared with the rest of the team.

3. **Committing Changes**:

   Commit your changes locally and push them to your fork:

   ```bash
   git push origin <branch-name>
   ```

4. **Opening a Pull Request (PR)**:

   Once you've pushed your branch to your fork, you can open a pull request from your fork's webpage on GitHub.

    - Please provide a clear PR message detailing the changes and motivations.
    - Ensure that your PR passes all continuous integration (CI) checks and adheres to our coding standards.
    - Remember that our repository has main branch protection. All code changes must be made through PRs.

5. **Code Reviews**:

   To ensure code quality and stability:

    - All PRs require at least one approval from a project maintainer or collaborator before merging.
    - Given that a successful merge will automatically build a binary for an OTA (Over-The-Air) update, reviews are critical. The binary will be made available immediately, so it's vital to ensure the quality and correctness of the code.

6. **Merging**:

   Once your PR has been approved, it will be merged into the main branch. As previously mentioned, this will automatically trigger a process to build an OTA update binary.

### Important Notes for Contributors

- Always ensure you are working on the latest version of the main branch. Regularly fetch and merge changes from the upstream main branch (the primary repository from which you forked) to avoid potential merge conflicts.

- When suggesting changes, always provide clear rationales and, if possible, references or further readings.

- Respect feedback from reviewers and maintain a professional and constructive discourse in the PR threads.

- If your PR addresses an open issue, please link to that issue in your PR description.

### Thank You!

Your contributions greatly help improve the library for the entire community. We genuinely appreciate the effort and expertise you bring in. Let's work together to make this library even better!

---

You can integrate this section into your `README.md`. Remember to replace placeholders (e.g., `<repository-name>`) and adjust any specific details to match the context of your project.

### Setting Up `pre-commit` for Development

#### Introduction

`pre-commit` is a tool that we use to maintain consistent code quality and format. It checks your changes before they're committed to ensure they adhere to our project's standards. This helps in reducing the chances of problematic or non-standard code entering the repository.

#### Installation & Configuration

1. **Install `pre-commit`**:

   Depending on your operating system and preferences, there are several ways to install `pre-commit`:

    - **Using `pip` (universal method)**:

      Ensure you have Python and `pip` installed on your machine. Then, run:
      ```bash
      pip install pre-commit
      ```

    - **Using Homebrew on macOS**:

      If you prefer using Homebrew on macOS, you can install `pre-commit` with the following command:
      ```bash
      brew install pre-commit
      ```

   If you're on another platform or if you're looking for other installation methods, check the [official documentation](https://pre-commit.com/#install) for `pre-commit`.

2. **Clone the Repository**:

   If you haven't already, clone the repository:
   ```bash
   git clone https://github.com/researchanddesire/OSSM-Software
   cd OSSM-Software
   ```

   Replace `https://github.com/researchanddesire/OSSM-Software` with the URL of this repository and `OSSM-Software` with the name of the directory where the repo was cloned.

3. **Install the Git Hook Scripts**:

   Inside the repository directory, run:
   ```bash
   pre-commit install
   ```

   This command installs the `pre-commit` hook.

4. **Using `pre-commit`**:

   From this point onwards, every time you run `git commit`, `pre-commit` will automatically check your changes. If there's a problem or if any files are auto-formatted, the commit will fail, and you'll receive a message detailing the changes made or issues found.

   If `pre-commit` auto-formats your code, you need to stage the changes with `git add` and then attempt your commit again.

#### Note to Developers

Always review any changes made by `pre-commit` to ensure they're expected and don't unintentionally modify the behavior of the code.

---

This revised section in your `README.md` should guide developers on multiple methods to install `pre-commit`. Ensure to adjust any placeholders or specific details to align with your project's context.
