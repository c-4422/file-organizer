#ifndef FILEOPERATION_HPP
#define FILEOPERATION_HPP

#include <QString>
#include <vector>

class FileOperation {
public:
  FileOperation();

  const std::vector<QString>& GetPicturesFileExt() const;
  QString GetOutputDestinantion();
  void SetOutputDestinantion(QString aOutputDestination);

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
    bool mIsMediaGrouping = false;
  };
  QString mOutputDestination{};
  FileSortSettings mPictures;
};

inline QString FileOperation::GetOutputDestinantion() { return mOutputDestination; }

inline void FileOperation::SetOutputDestinantion(QString aOutputDestination) {
  mOutputDestination = aOutputDestination;
}

#endif // FILEOPERATION_HPP
