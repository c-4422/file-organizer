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

const std::vector<QString>& FileOperation::GetPicturesFileExt() const {
    return mPictures.mFileExtensions;
}

void FileOperation::AddFileExt(Category aCategory, QString aString) {
  if (aCategory == Category::Picture) {
    auto it = mPictures.mFileExtensions.begin();
    mPictures.mFileExtensions.insert(it, aString);
  }
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
