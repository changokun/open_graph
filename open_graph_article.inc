<?php

class open_graph_article extends open_graph {

	const NS = 'og:article:';

	public $type = 'article';

	// article - Namespace URI: http://ogp.me/ns/article#
	// public static $article_properties = array('published_time', 'modified_time', 'expiration_time', 'author', 'section', 'tag');

	public static $published_time; // datetime - When the article was first published.
	public static $modified_time; // datetime - When the article was last changed.
	public static $expiration_time; // datetime - When the article is out of date after.
	public static $author; // profile array - Writers of the article.
	public static $section; // string - A high-level section name. E.g. Technology
	public static $tag; // string array - Tag words associated with this article.

	public function set_published_time(DateTime $date) { $this->published_time = $date->format('c'); }
	public function set_modified_time(DateTime $date) { $this->modified_time = $date->format('c'); }
	public function set_expiration_time(DateTime $date) { $this->expiration_time = $date->format('c'); }

	public function get_data_structure() {
		$data = array();
		foreach(array_keys(get_class_vars(get_called_class())) as $property_name) {
			if( ! empty($this->$property_name)) $data[] = static::NS . $property_name . ' ' . $this->$property_name;
		}
		return $data;
	}

	public function add_author(open_graph_profile $profile) {
		$this->author = $profile;
	}

}