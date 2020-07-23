##############################################################################
# This file is part of the TouchGFX 4.13.0 distribution.
#
# <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
# All rights reserved.</center></h2>
#
# This software component is licensed by ST under Ultimate Liberty license
# SLA0044, the "License"; You may not use this file except in compliance with
# the License. You may obtain a copy of the License at:
#                             www.st.com/SLA0044
#
##############################################################################

require 'json'

class TextKeysAndLanguages < Template
  def initialize(text_entries, typographies, output_directory)
    super
    @cache = {}
  end
  def countries
    text_entries.languages.map { |language| language.upcase }.join(",\n    ")
  end
  def texts
    text_entries.entries.map(&:cpp_text_id)
  end
  def input_path
    File.join(root_dir,'Templates','TextKeysAndLanguages.hpp.temp')
  end
  def output_path
    'include/texts/TextKeysAndLanguages.hpp'
  end
  def cache_file
    File.join(@output_directory, 'cache/TextKeysAndLanguages.cache')
  end
  def output_filename
    File.join(@output_directory, output_path)
  end
  def run
    @cache["languages"] = text_entries.languages
    @cache["textids"] = texts;

    new_cache_file = false
    if not File::exists?(cache_file)
      new_cache_file = true
    else
        #cache file exists, compare data with cache file
        old_cache = JSON.parse(File.read(cache_file))
        new_cache_file = (old_cache != @cache)
    end

    if new_cache_file
      #write new cache file
      FileIO.write_file_silent(cache_file, @cache.to_json)
    end

    if (!File::exists?(output_filename)) || new_cache_file || $Force_Generate_TextKeysAndLanguages
      #generate TextKeysAndLanguages.hpp
      super
    end
  end
end
