# From https://gist.github.com/vidavidorra/548ffbcdae99d752da02

set -e
echo 'Setting up the script...'
mkdir build-docs
cd build-docs

# Configure git.
git config --global push.default simple
git config user.name "Mayant Mukul"
git config user.email "mayantmukul@hotmail.com"

# Setup the repo
git clone -b gh-pages https://git@$GH_REPO_REF
cd $GH_REPO_NAME
rm -rf *
echo "" > .nojekyll

# Generate docs
echo 'Generating Doxygen code documentation...'
cd $TRAVIS_BUILD_DIR/docs
doxygen Doxyfile
cp -r html/** $TRAVIS_BUILD_DIR/build-docs/$GH_REPO_NAME

# Upload
cd $TRAVIS_BUILD_DIR/build-docs/$GH_REPO_NAME
if [ -f "index.html" ]; then
    echo 'Uploading documentation to the gh-pages branch...'
    git add --all
    git commit -m "docs: update for commit ${TRAVIS_COMMIT}"
    git push --force "https://${GH_REPO_TOKEN}@${GH_REPO_REF}" > /dev/null 2>&1
else
    echo '' >&2
    echo 'Warning: No documentation (html) files have been found!' >&2
    echo 'Warning: Not going to push the documentation to GitHub!' >&2
    exit 1
fi
