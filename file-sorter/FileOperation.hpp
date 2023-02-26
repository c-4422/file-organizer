#ifndef FILEOPERATION_HPP
#define FILEOPERATION_HPP

#include <QString>
#include <vector>

class FileOperation {
public:
  enum Category {
    Picture,
    Video,
    Document,
    Other
  };

  FileOperation();

  const std::vector<QString>& GetPicturesFileExt() const;
  QString GetOutputDestinantion();
  void SetOutputDestinantion(QString aOutputDestination);
  void AddFileExt(Category aCategory, QString aString);
  void RemoveFileExt(Category aCategory, int aIndex);
  void SetAllFileTypes(Category aCategory, bool aIsAllTypes);
  void SetDateSorted(Category aCategory, bool aIsDateSorted);
  void SetFileComment(Category aCategory, bool aIsFileComment);

private:
  struct FileSortSettings {
    FileSortSettings(std::vector<QString> aFileExtensions):
      mFileExtensions(aFileExtensions) {}
    FileSortSettings() {}

    std::vector<QString> mFileInput{};
    std::vector<QString> mFileExtensions{};
    QString mOutputDestination{};
    bool mIsDateSort = false;
    bool mIsFileComment = false;
    bool mIsAllFileTypes = false;
  };
  QString mOutputDestination{};
  FileSortSettings mPictures;
};

inline QString FileOperation::GetOutputDestinantion() { return mOutputDestination; }

inline void FileOperation::SetOutputDestinantion(QString aOutputDestination) {
  mOutputDestination = aOutputDestination;
}

#endif // FILEOPERATION_HPP
