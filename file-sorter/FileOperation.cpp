#include "FileOperation.hpp"

FileOperation::FileOperation() :
  mPictures(FileOperation::FileSortSettings({ "jpg", "jpeg", "jfi",
                                            "jpe", "jif", "jfif",
                                            "heif", "heic", "png",
                                            "gif", "svg", "svgz" "eps",
                                            "webp", "tiff", "tif", "ind",
                                            "indd", "indt", "idmi",
                                            "psd", "ai", "raw", "arw",
                                            "cr", "rw2", "nrw", "k25"})) {}

const std::vector<QString>& FileOperation::GetFileExt(Category aCategory) const {
  switch (aCategory) {
    case Category::Picture:
      return mPictures.mFileExtensions;
    case Category::Video:
      return mVideos.mFileExtensions;
    case Category::Music:
      return mMusic.mFileExtensions;
    case Category::Document:
      return mDocuments.mFileExtensions;
    case Category::Other:
      return mOther.mFileExtensions;
   }
}

const std::vector<FileOperation::DirectoryOutput>& FileOperation::GetInputDirectories(Category aCategory) const {
    switch (aCategory) {
      case Category::Picture:
        return mPictures.mInputDirectories;
      case Category::Video:
        return mVideos.mInputDirectories;
      case Category::Music:
        return mMusic.mInputDirectories;
      case Category::Document:
        return mDocuments.mInputDirectories;
      case Category::Other:
        return mOther.mInputDirectories;
    }
}

std::vector<FileOperation::DirectoryOutput>& FileOperation::GetInputDirectory(Category aCategory) {
  switch (aCategory) {
    case Category::Picture:
      return mPictures.mInputDirectories;
    case Category::Video:
      return mVideos.mInputDirectories;
    case Category::Music:
      return mMusic.mInputDirectories;
    case Category::Document:
      return mDocuments.mInputDirectories;
    case Category::Other:
      return mOther.mInputDirectories;
  }
}

QString FileOperation::GetOutputDestinantion(Category aCategory) const {
  switch (aCategory) {
    case Category::Picture:
      return mPictures.mOutputDestination;
    case Category::Video:
      return mVideos.mOutputDestination;
    case Category::Music:
      return mMusic.mOutputDestination;
    case Category::Document:
      return mDocuments.mOutputDestination;
    case Category::Other:
      return mOther.mOutputDestination;
  }
}

void FileOperation::AddFileExt(Category aCategory, QString aString) {
  if (aCategory == Category::Picture) {
    auto it = mPictures.mFileExtensions.begin();
    mPictures.mFileExtensions.insert(it, aString);
  }
}

int FileOperation::AddFileInputPath(Category aCategory, QString aString) {
  int returnIndex = 0;
  auto inputDirectory = GetInputDirectory(aCategory);
  // Check to see if we already have the input directory in the list
  auto it = find_if(inputDirectory.begin(), inputDirectory.end(), [&aString](const DirectoryOutput& obj) {return obj.mFolderInput == aString;});
  if (it != inputDirectory.end()) {
    // Input entry found return the index.
    returnIndex = std::distance(inputDirectory.begin(), it);
  } else {
    // Existing entry not found insert path.
    inputDirectory.insert(it, FileOperation::DirectoryOutput{aString});
  }
  return returnIndex;
}

void FileOperation::RemoveFileExt(Category aCategory, int aIndex) {
  if (aIndex < mPictures.mFileExtensions.size()) {
    mPictures.mFileExtensions.erase(mPictures.mFileExtensions.begin() + aIndex);
  }
}

void FileOperation::SetAllFileTypes(const Category aCategory, const bool aIsAllTypes) {
  switch (aCategory) {
    case Category::Picture:
      mPictures.mIsAllFileTypes = aIsAllTypes;

    default:
      break;
  }
}

void FileOperation::SetDateSorted(const Category aCategory, const bool aIsDateSorted) {
  switch (aCategory) {
    case Category::Picture:
      mPictures.mIsDateSort = aIsDateSorted;

    default:
      break;
  }
}

void FileOperation::SetFileComment(Category aCategory, bool aIsFileComment) {
  switch (aCategory) {
    case Category::Picture:
      mPictures.mIsFileComment = aIsFileComment;

    default:
      break;
  }
}

void FileOperation::SetOutputDestinantion(Category aCategory, QString aOutputDestination) {
  switch (aCategory) {
    case Category::Picture:
      mPictures.mOutputDestination = aOutputDestination;
      break;

    default:
      break;
  }
}

