<?php

/**
 * @file
 * Builds placeholder replacement tokens for node-related data.
 */

/**
 * Implements hook_token_info_alter().
 */
function publication_date_token_info_alter(&$data) {
  $data['tokens']['node']['published'] = array(
    'name' => t("Date published"),
    'description' => t("The date the node was first published."),
    'type' => 'date',
  );
  $data['tokens']['node']['published_or_now'] = array(
    'name' => t("Date published"),
    'description' => t("The date the node was first published, or the current time if never published."),
    'type' => 'date',
  );
  $data['tokens']['node']['published_or_created'] = array(
    'name' => t("Date published"),
    'description' => t("The date the node was first published, or the date created if never published."),
    'type' => 'date',
  );
  $data['tokens']['node']['published_or_changed'] = array(
    'name' => t("Date published"),
    'description' => t("The date the node was first published, or the date modified if never published."),
    'type' => 'date',
  );
}

/**
 * Implements hook_tokens().
 */
function publication_date_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $language_code = isset($options['language']) ? $options['language']->language : NULL;

  if ($type == 'node' && !empty($data['node'])) {
    $node = $data['node'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'published':
          $replacements[$original] = is_numeric($node->published_at) ? format_date($node->published_at, 'medium', '', NULL, $language_code) : '';
          break;

        case 'published_or_now':
          $replacements[$original] = is_numeric($node->published_at_or_now) ? format_date($node->published_at_or_now, 'medium', '', NULL, $language_code) : '';
          break;

        case 'published_or_created':
          $replacements[$original] = is_numeric($node->published_at_or_created) ? format_date($node->published_at_or_created, 'medium', '', NULL, $language_code) : '';
          break;

        case 'published_or_changed':
          $replacements[$original] = is_numeric($node->published_at_or_changed) ? format_date($node->published_at_or_changed, 'medium', '', NULL, $language_code) : '';
          break;
      }
    }

    if ($published_tokens = token_find_with_prefix($tokens, 'published')) {
      $replacements += token_generate('date', $published_tokens, array('date' => $node->published_at), $options);
    }
    elseif ($published_tokens = token_find_with_prefix($tokens, 'published_or_now')) {
      $replacements += token_generate('date', $published_tokens, array('date' => $node->published_at_or_now), $options);
    }
    elseif ($published_tokens = token_find_with_prefix($tokens, 'published_or_created')) {
      $replacements += token_generate('date', $published_tokens, array('date' => $node->published_at_or_created), $options);
    }
    elseif ($published_tokens = token_find_with_prefix($tokens, 'published_or_changed')) {
      $replacements += token_generate('date', $published_tokens, array('date' => $node->published_at_or_changed), $options);
    }
  }

  return $replacements;
}
