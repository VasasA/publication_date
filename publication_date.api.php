<?php

/**
 * @file
 * API documentation for the Publication Date module.
 */

/**
 * Alter the publication date before it is saved on node update/insert.
 *
 * @param int $published_at
 *   A Unix timestamp representing the publication date to be altered. If no
 *   publication date has been set then $published_at should equal the defined
 *   constant PUBLICATION_DATE_MAX.
 * @param object $node
 *   The node object.
 * @param string $op
 *   The node opperation being performed:
 *   - 'insert': A new node was created.
 *   - 'update': An existing node was updated.
 *
 * @see _publication_date_set_date()
 */
function hook_publication_date_alter(&$published_at, $node, $op) {
  // Check if the node is being published.
  if ($node->status == 1) {
    // If a future publication date was set, change it to the curret time.
    $published_at = ($published_at > REQUEST_TIME) ? REQUEST_TIME : $published_at;
  }
}
