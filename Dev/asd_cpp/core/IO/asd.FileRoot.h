﻿#pragma once

#include "../asd.Core.Base.h"
#include "asd.BaseFile.h"
#include "asd.PackFile.h"
#include "asd.Decryptor.h"

namespace asd
{
	/**
		@brief	ファイルのルートが保存されるクラス
	*/
	struct FileRoot
	{
	private:

	public:
		typedef std::shared_ptr<FileRoot> Ptr;

		astring m_path;
		std::shared_ptr<Decryptor> decryptor;

		std::shared_ptr<PackFile>	packFile;

		FileRoot(const astring& path, std::shared_ptr<Decryptor> decryptor)
			: decryptor(decryptor)
		{
			auto baseFile = std::shared_ptr<BaseFile>(new BaseFile(path), [](BaseFile* p){ SafeRelease(p); });

			if (baseFile->IsValid())
			{
				auto pack = std::make_shared<PackFile>();
				if (pack->Load(baseFile, decryptor.get()))
				{
					m_path = path;
					packFile = pack;
					return;
				}
			}

			decryptor.reset();
			m_path = FileHelper::ToRootDirectoryPath(path);
		}

		bool IsPackFile()
		{
			return packFile != nullptr;
		}

		std::shared_ptr<PackFile> GetPackFile() { return packFile; }

		bool operator== (const FileRoot& target) const
		{
			return decryptor == target.decryptor &&
				m_path == target.m_path;
		}
	};
}