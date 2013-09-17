<?php

class open_graph_article extends open_graph {

	public $type = 'article';

	// article - Namespace URI: http://ogp.me/ns/article#
	public static $article_properties = array('published_time', 'modified_time', 'expiration_time', 'author', 'section', 'tag');

	public static $published_time; // datetime - When the article was first published.
	public static $modified_time; // datetime - When the article was last changed.
	public static $expiration_time; // datetime - When the article is out of date after.
	public static $author; // profile array - Writers of the article.
	public static $section; // string - A high-level section name. E.g. Technology
	public static $tag; // string array - Tag words associated with this article.

}