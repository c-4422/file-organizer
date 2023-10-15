#include "FileOperation.hpp"

FileOperation::FileOperation()
    : mPictures(FileOperation::FileSortSettings({"jpg",
                                                 "jpeg",
                                                 "jfi",
                                                 "jpe",
                                                 "jif",
                                                 "jfif",
                                                 "heif",
                                                 "heic",
                                                 "png",
                                                 "gif",
                                                 "svg",
                                                 "svgz"
                                                 "eps",
                                                 "webp",
                                                 "tiff",
                                                 "tif",
                                                 "ind",
                                                 "indd",
                                                 "indt",
                                                 "idmi",
                                                 "psd",
                                                 "ai",
                                                 "raw",
                                                 "arw",
                                                 "cr",
                                                 "rw2",
                                                 "nrw",
                                                 "k25"})) {}

FileOperation::FileSortSettings *
FileOperation::GetFileSortSettings(const Category aCategory) {
  switch (aCategory) {
  case Category::Picture:
    return &mPictures;
  case Category::Video:
    return &mVideos;
  case Category::Audio:
    return &mAudio;
  case Category::Document:
    return &mDocuments;
  default:
    return &mOther;
  }
}

const FileOperation::FileSortSettings &
FileOperation::GetConstantFileSortSettings(const Category aCategory) const {
  switch (aCategory) {
  case Category::Picture:
    return mPictures;
  case Category::Video:
    return mVideos;
  case Category::Audio:
    return mAudio;
  case Category::Document:
    return mDocuments;
  default:
    return mOther;
  }
}

const std::vector<QString> &
FileOperation::GetFileExt(const Category aCategory) const {
  return GetConstantFileSortSettings(aCategory).mFileExtensions;
}

const std::vector<FileOperation::DirectoryOutput> &
FileOperation::GetInputDirectories(Category aCategory) const {
  return GetConstantFileSortSettings(aCategory).mInputDirectories;
}

const std::vector<QString> &
FileOperation::GetOutputDirectories(Category aCategory,
                                    const size_t aIndex) const {
  return GetConstantFileSortSettings(aCategory)
      .mInputDirectories[aIndex]
      .mFolderOutputs;
}

std::vector<FileOperation::DirectoryOutput> *
FileOperation::GetInputDirectory(Category aCategory) {
  return &GetFileSortSettings(aCategory)->mInputDirectories;
}

QString FileOperation::GetOutputDestinantion(Category aCategory) const {
  return GetConstantFileSortSettings(aCategory).mOutputDestination;
}

void FileOperation::AddFileExt(Category aCategory, QString aString) {
  auto fileSortSettings = GetFileSortSettings(aCategory);
  fileSortSettings->mFileExtensions.insert(
      fileSortSettings->mFileExtensions.begin(), aString);
}

int FileOperation::AddFileInputPath(Category aCategory, QString aString) {
  int returnIndex = 0;
  auto inputDirectory = GetInputDirectory(aCategory);
  // Check to see if we already have the input directory in the list
  auto it = find_if(inputDirectory->begin(), inputDirectory->end(),
                    [&aString](const DirectoryOutput &obj) {
                      return obj.mFolderInput == aString;
                    });
  if (it != inputDirectory->end()) {
    // Input entry found return the index.
    returnIndex = std::distance(inputDirectory->begin(), it);
  } else {
    // Existing entry not found insert path.
    inputDirectory->insert(it, FileOperation::DirectoryOutput{false, aString});
  }
  return returnIndex;
}

int FileOperation::AddSpecificOuputPath(const Category aCategory,
                                        const size_t aIndex, QString aString) {
  int returnIndex = 0;
  auto outputPaths =
      &GetFileSortSettings(aCategory)->mInputDirectories[aIndex].mFolderOutputs;
  // Check to see if we already have the output directory in the list
  auto it = find_if(outputPaths->begin(), outputPaths->end(),
                    [&aString](const QString &memberString) {
                      return memberString == aString;
                    });
  if (it != outputPaths->end()) {
    // Input entry found return the index.
    returnIndex = std::distance(outputPaths->begin(), it);
  } else {
    // Existing entry not found insert path.
    outputPaths->insert(it, aString);
  }
  return returnIndex;
}

void FileOperation::RemoveFileInputPath(const Category aCategory,
                                        const size_t aIndex) {
  if (auto fileSortSettings = GetFileSortSettings(aCategory);
      aIndex < fileSortSettings->mInputDirectories.size()) {
    fileSortSettings->mInputDirectories.erase(
        std::next(fileSortSettings->mInputDirectories.begin(), aIndex));
  }
}

void FileOperation::RemoveFileExt(const Category aCategory,
                                  const size_t aIndex) {
  if (auto fileSortSettings = GetFileSortSettings(aCategory);
      aIndex < fileSortSettings->mFileExtensions.size()) {
    fileSortSettings->mFileExtensions.erase(
        std::next(fileSortSettings->mFileExtensions.begin(), aIndex));
  }
}

void FileOperation::SetAllFileTypes(const Category aCategory,
                                    const bool aIsAllTypes) {
  GetFileSortSettings(aCategory)->mIsAllFileTypes = aIsAllTypes;
}

void FileOperation::SetDateSorted(const Category aCategory,
                                  const bool aIsDateSorted) {
  GetFileSortSettings(aCategory)->mIsDateSort = aIsDateSorted;
}

void FileOperation::SetFileComment(const Category aCategory,
                                   const bool aIsFileComment) {
  GetFileSortSettings(aCategory)->mIsFileComment = aIsFileComment;
}

void FileOperation::SetOutputDestinantion(const Category aCategory,
                                          QString aOutputDestination) {
  GetFileSortSettings(aCategory)->mOutputDestination = aOutputDestination;
}

void FileOperation::SetMultiDestination(const Category aCategory,
                                        const size_t aIndex,
                                        const bool aIsMultiDestination) {
  if (const auto *fileSortSettings = GetFileSortSettings(aCategory);
      aIndex < fileSortSettings->mInputDirectories.size())
    GetFileSortSettings(aCategory)
        ->mInputDirectories[aIndex]
        .mIsMultiDestination = aIsMultiDestination;
}
